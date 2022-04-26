import os

libs   = ['tfhe', 'seal']
cases  = ['bridge', 'comb', 'spec']
benchs  = [4, 8, 16, 32]
root   = '../../../..'
dir    = 'user/isca/case/pir'
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
                user = '{}/{}/pir{}'.format(dir,case,bench)
                cgt  = '{}/../cgt_{}{}.cfg'.format(dir,lib,bench)
                fout = '{}/{}/pir{}_{}_{}.txt'.format(dir,res,bench,case,lib)
                os.system('cd {0} && rm -f secint.* && \
                    export LD_LIBRARY_PATH=. && \
                    make bob USER={1} CGT={2} {3}=1 && \
                    ./bob.exe > {4}\
                    '.format(root, user, cgt, lib.upper(), fout)
                )

if __name__ == '__main__':
    main()
