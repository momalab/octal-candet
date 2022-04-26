import os

libs   = ['tfhe', 'seal']
libs   = ['seal']
cases  = ['bridge', 'comb', 'spec']
cases  = ['bridge', 'comb']
cases  = ['comb']
benchs = [4, 8, 16, 32]
benchs = [32]
root   = '../../../..'
dir    = 'user/isca/case/matrix'
res    = 'results'

def main():
    if not os.path.isdir(res):
        os.system('mkdir {}'.format(res))
    for lib in libs:
        os.system( 'cd {} && make c'.format(root) )
        for case in cases:
            if case=='spec':
                os.system('cp spec/circuits_{}.inc spec/circuits.inc'.format(lib));
            elif lib=='tfhe' and case=='bridge':
                continue
            for bench in benchs:
                user = '{}/{}/matrix{}'.format(dir,case,bench)
                cgt  = '{}/../cgt_{}{}.cfg'.format(dir,lib,bench)
                fout = '{}/{}/matrix{}_{}_{}.txt'.format(dir,res,bench,case,lib)
                os.system('cd {0} && rm -f secint.* && \
                    export LD_LIBRARY_PATH=. && \
                    make bob USER={1} CGT={2} {3}=1 && \
                    ./bob.exe > {4}\
                    '.format(root, user, cgt, lib.upper(), fout)
                )

if __name__ == '__main__':
    main()
