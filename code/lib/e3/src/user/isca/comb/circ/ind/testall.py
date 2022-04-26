import os

cgts = ['seal', 'seals', 'tfhe', 'heli', 'helis']
libs = ['SEAL', 'SEAL' , 'TFHE', 'HELI', 'HELI' ]
root = '../../../../..'
user = 'user/isca/comb/circ/ind'
res  = 'results'

def main():
    if not os.path.isdir(res):
        os.system('mkdir {}'.format(res))
    for i,cgt in enumerate(cgts):
        lib = libs[i]
        cmd = '\
            cd {0} && \
            make c && \
            make USER={1} CGT={1}/cgt_{2}.cfg {3}=1 && \
            ./bob.exe 60 > {1}/{4}/{2}_2_8.txt \
        '.format(root, user, cgt, lib, res)
        print(cmd)
        os.system(cmd)

if __name__ == '__main__':
    main()
