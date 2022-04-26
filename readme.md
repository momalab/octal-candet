# Octal-CanDet
The repository consists of all the scripts, data and source code for fast and scalable private cancer/tumor classification using The Cancer Genome Atlas (TCGA) data. We specifically use Single Nucleotide Variation (SNV) and Copy Number Variation (CNV) from patient data to predict cancer type. The repository contains a list of top important genes extracted using our feature engineering methods (/code/training/) and a parser (/code/app/parser.sh) that reads CNV and SNV information of test data and converts into .tmp files with encoded features. We also include the training script for updating the model.

## Plain-text
### Dependencies
* python 3.6.5
* keras 2.3.1
* scikit-learn 0.23.2
* numpy 1.19.2

1. Clone octal-candet:
```
git clone https://github.com/momalab/octal-candet.git
```
2. Change directory to code/training:
```
cd code/training
```
3. Run training script:
```
python trainingScript.py <path_to_original_dataset"/Dataset">
```


## Private Inference using the BFV

### Setup
Unzip data: data/Test_CNs.zip, data/Test_variats.zip
```
unzip data/Test_CNs.zip
unzip data/Test_variants.zip
```


### Run

### TL;DR
1. Compile and run everything for all databases:
```
cd idash2020/slim/code/app
make compile && make
```

The script will automatically call all steps: parse, encryption, query, decryption and will report the timing for privacy-preserving cancer classification.

Files of interest:
* inputs: Test_samples.txt, Test_CNs.txt, Test_variats.txt in data/data
* weights: Weights.txt, Bias.txt in data/server/<no_of_features_used>

### Cite us:
E. Sarkar, E. Chielle, G. Gürsoy, L. Chen, M. Gerstein and M. Maniatakos, "Scalable privacy-preserving cancer type prediction with homomorphic encryption", 2022, arXiv:2204.05496
```
@misc{sarkar2022scalable,
      title={Scalable privacy-preserving cancer type prediction with homomorphic encryption}, 
      author={Esha Sarkar and Eduardo Chielle and Gamze Gursoy and Leo Chen and Mark Gerstein and Michail Maniatakos},
      year={2022},
      eprint={2204.05496},
      archivePrefix={arXiv},
      primaryClass={cs.CR}
}
```
