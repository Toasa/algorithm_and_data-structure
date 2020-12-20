def power_set(N):
    s = ":0{}b".format(N)
    s = "{" + s + "}"
    for i in range(0, 1<<N):
        print(s.format(i))

power_set(3)
