# 2018-10-10

# mビットのビット配列Bを予め用意する。ただし、中身はすべて0.
# 集まりの集合Cの要素uに対し、0からmまでの整数値の中でhash(u) = k個
#（これがビット配列のインデックスになる）を選ぶ。そのk個の数字をBのインデックスとして
# ビットを1にする。
# 例えば、m=10, Cにu, vがあったとし、k = 3とする。
# またhash(u) = 1, 3, 8, hash(v) = 2, 4, 8となったとする。
# このときビット配列Bは

#   0   1   2   3   4   5   6   7   8   9  10
# ---------------------------------------------
# | 0 | 1 | 1 | 1 | 1 | 0 | 0 | 0 | 1 | 0 | 0 |
# ---------------------------------------------

# となる。
# また、hash(w) = 1, 2, 6, hash(x) = 1, 2, 3となる値 w, xがあったとする。
# ビット配列Bを見ると、値wがB内には挿入されていないことがすぐに分かる。
# (index6のbitが立っていないから。)つまり, false negativeは起こりえない。
# だが、値xはBに挿入していないが、hash(x)のbitが立ってしまっている。
# つまり、false positiveは起こりうる。

import random

class bloomFilter:
    # size個のbit配列self.bit_arrayを作り、複数のhash関数を定義する
    def __init__(self, size=100):
        self.bit_array = 0
        self.size = size

        # # 通常の関数定義
        # def funcName(arg1, arg2, arg3):
        #     return val
        #
        # # pythonのlambda関数
        # funcName = lambda arg1, arg2, arg3: val

        # divsは互いに素な整数を選択する
        # -> hash関数の性能をあげる（false positiveの可能性を減らす）
        # divs = [23, 79]
        divs = [23, 33]
        self.hashFuncs = [lambda e : hash(e) % divs[0], lambda e : hash(e) % divs[1]]

    # bloom filterに値を登録する
    def add(self, value):
        for hf in self.hashFuncs:
            self.bit_array |= (1 << hf(value))

    # 値があるかどうか判定する。
    def contains(self, value):
        for hf in self.hashFuncs:
            if self.bit_array & (1 << hf(value)) == 0:
                return False

        # 値valueがあるかもしれない
        return True

    # divsの性能を測る
    def test_divs_performance(self, check_num=30, test_times=10000):
        count_not = 0
        for i in range(test_times):
            A = random.sample(list(range(300)), 50)
            bf = bloomFilter()
            for n in A:
                bf.add(n)
            if bf.contains(check_num):
                continue
            else:
                count_not += 1
        print("Definitely value not in...")
        print("accuracy: {0}%".format(count_not / test_times * 100))

    # bloomFilterの試行
    # 0...300の整数の中から、ランダムに重複なく50個を選び、
    # bloom filterに通す。そして整数30がもとの50個の中にあったかを判断する.
    # 絶対にない、もしくは、あるかもしれない、という結果を表示する.
    def test(self, check_num=30):
        A = random.sample(list(range(300)), 50)
        print(sorted(A))
        for n in A:
            self.add(n)
        if self.contains(check_num):
            print("{0}: may be in Array".format(check_num))
        else:
            print("{0}: definitely be not in Array".format(check_num))


bf = bloomFilter()

#bf.test_divs_performance()
bf.test()
