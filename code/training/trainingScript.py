# import libraries
import sys
import pandas as pd
import numpy as np
import os
import itertools
from sklearn.model_selection import train_test_split
from sklearn import preprocessing
from sklearn.linear_model import LogisticRegression
from sklearn.svm import SVC
from numpy import array
from sklearn.model_selection import KFold
from sklearn.feature_selection import SelectKBest, chi2, mutual_info_classif, mutual_info_classif
import pickle

# Get all the files in the format Tumour1_challenge_CNs.txt, Tumour1_challenge_variants.txt, Tumour1_challenge_samples.list
orig_datapath = sys.argv[1]

CN_files = [f for f in os.listdir(orig_datapath) if 'CNs' in f]
Samples_files = [f for f in os.listdir(orig_datapath) if 'samples' in f]
Variants_files = [f for f in os.listdir(orig_datapath) if 'variants' in f]

labels = [l.split('_')[0] for l in CN_files]
ids = np.array([])
y_train = np.array([])
for sf in Samples_files:
    ids_temp = np.loadtxt(os.path.join(orig_datapath,sf),dtype = 'U18')
    ids = np.concatenate((ids,ids_temp))
    y_train_temp =  np.array([sf.split('_')[0]]*len(ids_temp))
    y_train = np.concatenate((y_train,y_train_temp))
print (labels)
y_train = np.array(y_train)


# Get CN data
cn_data_df = []
cn_labels = []
ctr = 0
for n in range(len(CN_files)):
    temp = (pd.read_csv(os.path.join(orig_datapath,CN_files[n]),sep='\t', index_col=0)).T
    cn_data_df.append(temp)
    cn_labels.append([labels[n]]*len(temp))
cn_data_df = pd.concat(cn_data_df)
cn_labels = list(itertools.chain.from_iterable(cn_labels))

X_train_cn = (cn_data_df.T[ids]).T
X_train_cn = X_train_cn.to_numpy()
print ("Shape of CN-based train and test data: ",X_train_cn.shape)


# Get the top genes according to mutation frequency per tumour
top_genes = []
for i in range(11):
    top_genes_temp = list(np.loadtxt('top_genes'+labels[i]+'.txt',dtype=str))
    top_genes = top_genes + (top_genes_temp)
top_genes = list(set(top_genes))
print ("Number of genes: ", len(top_genes))

# Make the dataset according to the effect of mutations
training_data = np.zeros((len(ids)+1,len(top_genes)+1),dtype = 'U18')
training_data[0,1:] = top_genes
training_data[1:,0] = ids

# Encoding 8th column
encoding_dict_8 = {'LOW': 0.1,
                'MODERATE':0.5,
                'MODIFIER':0.75,
                'HIGH':1,
                 }
# Encoding 7th column
encoding_dict_7 = {'0':0,
                 'deleterious':0.5,
                 'deleterious_low_confidence':0.25,
                 'tolerated_low_confidence':-0.25,
                 'tolerated':-0.5}
def changeData(temp):
    first_part = []
    second_part = []
    temp2 = [j.split('(') for j in temp[:,6]]
    for i in temp2:
        if i[0]!='.':
            first_part.append(i[0])
            second_part.append(i[1][:-1])
        else:
            first_part.append(0)
            second_part.append(0)      
        data = np.zeros((temp.shape[0],temp.shape[1]+1))
    data = np.zeros((temp.shape[0],temp.shape[1]+1),dtype = 'U32')
    data[:,:6]=temp[:,:6]
    data[:,6]=np.array(first_part)
    data[:,7]=np.array(second_part)
    data[:,8]=temp[:,7]
    return (data)

for i in range(1):
    print ("Extracting label",i)
    #print (labels[i])
    #print (y_train)
    ind = np.where(np.array(y_train) == labels[i])[0]
    #print (ind) 
    training_ids_temp = ids[ind]
    variant_file = labels[i]+'_challenge_variants.txt'
    temp = ((pd.read_csv(os.path.join(orig_datapath,variant_file),sep='\t',  header=None))).to_numpy()
    print ("Number of individuals in this label: ",len(training_ids_temp))
    #print (len(ind))
    temp2 = changeData(temp)
    for num_patient,patient in enumerate(training_ids_temp):
        #print (patient)
        indices1 = np.where(temp2[:,0] == patient)[0]
        genes_temp = temp2[indices1,1] # name of genes
        effect_temp = temp2[indices1,-1] # last column
        impact_temp = temp2[indices1,-3] # Second last column split in type and value
        impact_val_temp = temp2[indices1,-2]

        effect_num = []
        for j in effect_temp:
            effect_num.append(encoding_dict_8[j])
        effect_num = np.array(effect_num)

        impact_num = []
        for val_num,k in enumerate(impact_temp):
            impact_num.append(encoding_dict_7[k]*float(impact_val_temp[val_num]))
        impact_num = np.array(impact_num)    


        unique_genes = set(list(genes_temp))
        gene_dict = {}
        #print (gene_dict)
        for ug in unique_genes:
            #print (ug)
            effect = effect_num[np.where(genes_temp==ug)[0][0]]# just 8th column

            #effect = np.sum(effect_num[np.where(genes_temp==ug)[0]])+np.sum(impact_num[np.where(genes_temp==ug)[0]])
            #print (effect)
            #print ('-----------------------------')
            gene_dict[ug]=effect
        for gene in list(gene_dict.keys()):
            row = np.where(training_data[:,0]==patient)[0][0]
            #print (row)
            try:
                col = np.where(training_data[0,:]==gene)[0][0]
                #print (col)
                training_data[row,col] = gene_dict[gene]
            except:
                pass
training_data[training_data == '']='0'   
X_train_va = (training_data[1:,1:]).astype('float')
Xtr_all = np.hstack((X_train_cn+2,X_train_va))

le = preprocessing.LabelEncoder()
ytr_num = le.fit_transform(y_train.reshape(-1,))

print ("Shapes of training data: ",X_train_cn.shape, X_train_va.shape, Xtr_all.shape, ytr_num.shape)
def fit_model(m,x,y):
    kfold = KFold(5, shuffle = True, random_state = 1)
    ctr = 0
    for train, test in kfold.split(x):
        print (ctr)
        m.fit(x[train],y[train])
        ctr = ctr+1
    return(m)

i = 40960

fs = SelectKBest(chi2, k=i)
fs.fit(Xtr_all, ytr_num)
X_train_fs = fs.transform(Xtr_all)

model = LogisticRegression(penalty='l1',solver='liblinear', max_iter=10000, multi_class='auto')
model = fit_model(model,X_train_fs,ytr_num)
yhat = model.predict(X_train_fs)
accuracy = np.mean(ytr_num == yhat)
#filename = 'Full_train/model_'+'final'+'_'+str(i)+'.sav'
#pickle.dump(model, open(filename, 'wb'))
print('Accuracy: ', (accuracy*100), 'for number of features: ',i)