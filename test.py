from copy import deepcopy

sizes = [4, 7, 8, 8, 10, 5, 1, 3] 
inc = 0

length = 1;
for i in sizes:
    length *= i

values = [""]*length
arr = ["ta", "na", "may", "new", "lk", "wa", "ik", "pa", "ca", "egi", "soun", "gh", "ov", "ou", "au", "it", "ai", "go", "oo", "ri", "rt", "ni", "top", "ou", "tt", "th", "rn", "sw", "ow", "ma", "ik", "wa", "nk", "xa", "ill", "ot", "sp", "ed", "eg", "ll", "il", "mo", "ht", "wr", "lm", "pi"]
sizes_0 = sizes[0] + sizes[1]
sizes_1 = sizes_0 + sizes[2]
sizes_2 = sizes_1 + sizes[3]
sizes_3 = sizes_2 + sizes[4]
sizes_4 = sizes_3 + sizes[5]
sizes_5 = sizes_4 + sizes[6]
sizes_6 = sizes_5 + sizes[7]
for i in range(sizes[0]):  ############ range sizes[1] and > should start from sizes[0:prev_indexes] to the sizes[0:prev_indexes] + sizes[1]...
    for j in range(sizes[0], sizes_0):
        for k in range(sizes_0, sizes_1):
            for n in range(sizes_1, sizes_2):
                for m in range(sizes_2, sizes_3):
                    for r in range(sizes_3, sizes_4):
                        for q in range(sizes_4, sizes_5):
                            for c in range(sizes_5, sizes_6):
                                values[inc] = arr[i] + arr[j] + arr[k] + arr[n] + arr[m] + arr[r] + arr[q] + arr[c]
                                print(values[inc])
                                inc+=1


# same algorithm recursively
sizes_x = []
sizes_copy = deepcopy(sizes);
for i in range(len(sizes)):
    prod = 1
    for j in sizes_copy:
        prod *= j

    sizes_copy.remove(sizes_copy[0])
    sizes_x.append(prod)

# index is sizes index
def additive(sizes_x: list, values: list, sizes: list, arr: list, index: int):
    for i in range(sizes_x[index]):
        values[i] += arr[index] # arr index should be range(4) when index = 0
    
    index+=1
    if index != len(sizes_x):
        additive(sizes_x, values, sizes, arr, index)
    else:
        return 1

index = 0
values = [""]*length

# //sizes_x[#] replace # with iterating values and the divison should include 0 to #. if # = 4, it should be i // sizes_x[0:3]

sizes_x_h = []
for i in sizes_x:
    tmp = sizes_x[0:i]
    temp_size = 1
    for i in tmp:
        temp_size*=i
    sizes_x_h.append(temp_size)

#print(sizes_x_h)

#additive(sizes_x, values, sizes, arr, index)
for i in range(sizes_x[0]):
    values[i] = arr[i//sizes_x_h[0]] + arr[i//sizes_x_h[1]] + arr[i//sizes_x_h[2]] + arr[i//sizes_x_h[3]]  + arr[i//sizes_x_h[4]] + arr[i//sizes_x_h[5]]+ arr[i//sizes_x_h[6]] + arr[i//sizes_x_h[7]]

#for i in values:
#    print(i)
