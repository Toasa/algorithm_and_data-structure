# 2018-10-08

# collectionの中に、tが存在するか否か、bool値で返す
# 単にcollectionの中を一つずつ見て、一致するかを探索する力任せのアルゴリズム
def sequentialSearch(collection, t):
    for e in collection:
        if e == t:
            return True
    return False

# ex
a = ["Brady", "Gurley", "Newton"]
print(sequentialSearch(a, "Gronkowski"))

b = list(range(100))
print(sequentialSearch(b, 46))
