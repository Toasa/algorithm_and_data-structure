A = [1, 13, 32, 51, 51, 51, 73, 82]

def is_ok(i, val):
    return A[i] >= val

# 配列 A の index のうち val 以上となる
# 最小の index を返す
def bi_search(val):
    ng = -1 # index = 0 が条件を満たす場合もあるので
            # ng のインデックスは -1 からはじめる
    ok = len(A) # index = len(A) - 1 が条件を満たさない場合もあるので
                # ok のインデックスは len(A) からはじめる
    while abs(ok - ng) > 1:
        mid = (ok + ng) // 2
        if is_ok(mid, val):
            ok = mid
        else:
            ng = mid

    return ok

def main():
    print(bi_search(1))
    print(bi_search(32))
    print(bi_search(50))
    print(bi_search(51))
    print(bi_search(73))
    print(bi_search(100))

main()


    



