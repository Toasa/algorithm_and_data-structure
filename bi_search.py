import random

def make_random_int_list():
    l = []
    for i in range(10):
        n = int(random.uniform(0, 101))
        l.append(n)
    return sorted(l)

def bi_search(l, num):
    # 半開区間で二分探索を行う
    # この実装では左端は実在のインデックス
    # 右端は実在しないインデックス
    # このとき左端(min_i) が常に実在のインデックスになるので
    # 値の存在判定もmin_iの場所と比べればよく楽
    min_i = 0
    max_i = len(l)

    while abs(max_i - min_i) > 1:
        mid_i = (max_i + min_i) // 2
        if l[mid_i] > num:
            max_i = mid_i
        else:
            min_i = mid_i

    if l[min_i] == num:
        if not (num in l):
            print("{} in {}".format(num, l))
    else:
        if num in l:
            print("Not {} in {}".format(num, l))

def main():
    for i in range(100000):
        l = make_random_int_list()
        n = int(random.uniform(0, 101))
        bi_search(l, n)

main()

