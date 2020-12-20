def makeSuffxArray(S):
    l = []
    for i in range(len(S)):
        l.append(S[i:])
    l.sort()
    return l

def bi_search(l, s):
    min_i = 0
    max_i = len(l)

    while abs(max_i - min_i) > 1:
        mid_i = (max_i + min_i) // 2
        if l[mid_i] > s:
            max_i = mid_i
        else:
            min_i = mid_i

    if l[min_i] == s:
        print("Found: {}".format(min_i))
    else:
        print("Not found")

def main():
    S = "abracadabra"
    l = makeSuffxArray(S)
    bi_search(l, "abra")
    bi_search(l, "brac")

main()
