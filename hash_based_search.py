# 2018-10-09

# 要素が多い集まりや整列されていない集まり上での探索に向いている
# hash関数がおおよそ均等に要素を分散すると、hash_based_searchは優れた性能になる

# 集まり内の要素が取りうる上限値
MAX_VALUE = 1000
# 集まり内の要素数
LEN_OF_A = 500
# hash_tableの長さ
TABLE_SIZE = 100

import random

def hash(n):
    return n % TABLE_SIZE

def makeHashTable(A, table):
    for i in A:
        # table[j]内にすでに値がある場合（collision）もappendすれば良い
        # 教科書ではlinked-listで格納する方法と、オープンアドレス法が書かれていた
        table[hash(i)].append(i)
    return table

# 集まりA内にnが存在するか?
def search(A, n, table):
    for i in table[hash(n)]:
        # hash関数でnのtable配列のindexを求めたあとは、for文による逐次探索
        if i == n:
            return True

    return False


l = list(range(MAX_VALUE))
# 集まりの配列(0からMAX_VALUEまでの配列から、LEN_OF_A個をランダムに選択し、リスト化)
A = random.sample(l, LEN_OF_A)

# hash_tableの初期化
table = [[] for row in range(TABLE_SIZE)]
# hash_tableの作成
table = makeHashTable(A, table)


check_num = 30
if search(A, check_num, table):
    print("{0}: found".format(check_num))
else:
    print("{0}: not found".format(check_num))

print(table)
