"""
By: Taha Canturk (Kibnakamoto)
Github: Kibnakamoto
Date: Jul 17, 2023

OneTimePad licenced under the GNU General Public Licence
"""

# python file for cracking the plaintexts using the bigram data

from secrets import randbelow
from decimal import Decimal
import time
import sys
import readline

import dotart

options = ["--no-fill"]

def onetimepad(x:str,y:str) -> str:
    ret = ""
    for i in range(len(x)):
        ret += chr(ord(x[i]) ^ ord(y[i]))
    return ret

# str to hex
def hx(x):
    ret = ""
    for i in x:
        ret += hex(ord(i))[2:].zfill(2)
    return ret

def unieqe_len(lst):
    s = set(lst)
    sizes = [0]*len(s)
    i=0
    for e in s:
        for j in lst:
            if j == e:
                sizes[i]+=1
        i+=1
    return sizes


# seperate every ith value
def sep(string, i=2) -> list:
    lst = []
    for j in range(0, len(string), i):
        lst.append(string[j:j+i])
    return lst

def warning(msg):
    print("\033[95;1;5mwarning: \033[0m\033[1;95;23m", msg, "\033[0m")

def message(msg):
    print("\033[95;3m[msg] \033[0m\033[95;23m", msg, "\033[0m")

def add(string, i):
    return string[:i] + ' ' + string[i:]

def rm(string, i):
    return string[:i] + string[i+1:]


# set general data variables
with open("out/data.txt", "r") as f:
    data_txt = f.readlines()
    length = int(data_txt[0].replace("len: ", ""))
    m1m2_tmp = data_txt[1].replace("m1m2: ", "")[:-1]
    ct1_tmp = data_txt[2].replace("ct1: ", "")[:-1]
    ct2_tmp = data_txt[3].replace("ct2: ", "")[:-1]
    m1m2 = bytes(bytearray.fromhex(m1m2_tmp))
    ct1 = bytes(bytearray.fromhex(ct1_tmp))
    ct2 = bytes(bytearray.fromhex(ct2_tmp))


print("\033[1;32mlength of message:\t\033[0m", length)
print("\n\x1b[1;31mciphertext 1(ct1):\t\x1b[0m\033[37;1m ", ct1_tmp, "\033[0m")
print("\x1b[1;31mciphertext 2 (ct2):\t\x1b[0m\033[37;1m ", ct2_tmp, "\033[0m")
print("\n\x1b[1;31mm1 xor m2 (m1m2):\t\x1b[0m\033[37;1m ", m1m2_tmp, "\033[0m")
print()

inc = 100//length
start_time = time.time()
# Data format: index: {x,y} where x xor y = m1m2. X and Y = can be plaintexts and ciphertexts (with same key). results in the same OneTimePad Exploit
pt1_progress_bar = ""
# first use bigrams
with open("out/bigrams.txt", "r") as f:
    # calculate possible plaintext using bigrams
    bigrams_txt = f.readlines()
    bigrams_len = int(bigrams_txt[0].replace("bigram count: ", ""))
    bigrams_txt.remove(bigrams_txt[0]) # remove first index (len)
    bigram_indexes = []
    bigrams_p1 = []
    bigrams_p2 = []
    all_lines = ""

    # set bigrams and bigram indexes
    for line in bigrams_txt:
        index = int(line.partition(":")[0])
        start = line.index("{")
        end = line.index("}")
        first = line[start+1:start+3]
        second = line[end-2:end]
        xored = onetimepad(first, second)

        if hx(xored) != m1m2_tmp[index*2:index*2+4]:
            warning("found a NON-matching m1m2 bigram ciphertext")
            message(f"{first} xor {second} !=  {m1m2_tmp[index*2:index*2+4]}")
            message(hx(onetimepad(first, second)) + " != " + m1m2_tmp[index*2:index*2+4])
            bigrams_txt.remove(line)
            continue
        bigram_indexes.append(index)
        bigrams_p1.append(first)
        bigrams_p2.append(second)
        all_lines += line + "\n"

    sys.stdout.write("\r")
    sys.stdout.write("\x1b[4;2;1;38;2;7;224;21m%-100s\t\t\033[1;38;2;7;224;21m%d%%\033[0m" % ("", 0))

    with open("out/bigram.py", "w") as file:
        file.write("import sys\n")
        file.write('''def onetimepad(x:str,y:str) -> str:
    ret = ""
    for i in range(len(x)):
        ret += chr(ord(x[i]) ^ ord(y[i]))
    return ret\n''')
        file.write('''\ndef hx(x):
    ret = []
    for i in x:
        ret.append(hex(ord(i))[2:].zfill(2))
    return ret\n''')
        file.write(f"\nb1 = {bigrams_p1}\nb2 = {bigrams_p2}\nm1m2={sep(m1m2_tmp)}\nwith open(\"out/bigram_out.txt\", \"w+\") as f:\n")
        sizes = unieqe_len(bigram_indexes)
        num = sizes[0]
        prev_num = 0

        for i in range(len(sizes)):
            file.write("    "*(i+1) + f"for i{i} in range({prev_num}, {num}):\n")
            if i != len(sizes)-1:
                num += sizes[i+1]
            prev_num += sizes[i]
        tabs = len(sizes)*"    " + "    "
        file.write(f"{tabs}string = list(\" \"*{length})")
        file.write(f"\n{tabs}string2 = list(\" \"*{length})")
        file.write(f"\n{tabs}ind = {list(set(bigram_indexes))[0]}") # do while
        file.write(f"\n{tabs}string[ind] = b1[i0][0]")
        file.write(f"\n{tabs}string[ind+1] = b1[i0][1]")
        file.write(f"\n{tabs}string2[ind] = b2[i0][0]")
        file.write(f"\n{tabs}string2[ind+1] = b2[i0][1]")
        for i in range(1, len(sizes)):
            file.write(f"\n{tabs}ind = {list(set(bigram_indexes))[i]}")
            if list(set(bigram_indexes))[i-1]+1 != list(set(bigram_indexes))[i]: # to make sure the whole bigram is added rather than one byte replaced later
                file.write(f"\n{tabs}string[ind] = b1[i{i}][0]")
                file.write(f"\n{tabs}string2[ind] = b2[i{i}][0]")
            file.write(f"\n{tabs}string[ind+1] = b1[i{i}][1]")
            file.write(f"\n{tabs}string2[ind+1] = b2[i{i}][1]")
        if "--no-fill" not in sys.argv:
            file.write(f"\n{tabs}for ind in range({length}):")
            file.write(f"\n{tabs}    while hx(onetimepad(string, string2))[ind] != m1m2[ind]:") # if index doesn't match
            file.write(f"\n{tabs}        number = 32") # 32 is ' '
            file.write(f"\n{tabs}        for i in range(97,122):") 
            file.write(f"\n{tabs}            if number ^ i == int(m1m2[ind], 16):") # generate index from ascii encoding 65 to 123 (common letters and symbols)
            if randbelow(2) == 1: # flip coin to see who should get space
                file.write(f"\n{tabs}                string[ind] = chr(number)")
                file.write(f"\n{tabs}                string2[ind] = chr(i)")
                file.write(f"\n{tabs}                break")
            else:
                file.write(f"\n{tabs}                string2[ind] = chr(number)")
                file.write(f"\n{tabs}                string[ind] = chr(i)")
                file.write(f"\n{tabs}                break")
        file.write(f"\n{tabs}strings = \"\\\"\" + \'\'.join(i for i in string) + \"\\\" : \\\"\" + \'\'.join(i for i in string2) + \"\\\"\"")
        # file.write(f"\n{tabs}print(strings)")
        file.write(f"\n{tabs}f.write(strings + \"\\n\")")
        file.write(f"\n        progress=(i0+1)*100//({sizes[0]})")
        file.write("\n        progress_bar=\"_\"*progress")
        file.write("\n        sys.stdout.write(f\"\\r\")")
        file.write("\n        sys.stdout.write(\"\x1b[4;2;1;38;2;7;224;21m%-100s\t\t\033[1;38;2;7;224;21m%d%%\033[0m\" % (progress_bar, progress))")
    with open("out/bigram.py") as f:
        exec(f.read()) # run the file

    print("\n\x1b[1;5;34mFinished in \t\x1b[0m\033[37;1m ", Decimal(time.time()-start_time), "\033[0m\x1b[1;34ms\x1b[0m")

    print("\n\x1b[1;32mData successfully Generated...\x1b[0m")
    print("\n\x1b[1;mAll sentences generated satisfy the requirement of m1m2, the raw data can be processed at your own discression...\x1b[0m")
    print("\n\x1b[1;mThe data is saved in out/bigram_out.txt\x1b[0m")

    # with open("out/bigram_out.txt", "r+") as f:
    #     # check the indexes and correct them
    #     lines = f.readlines()
    #     for line in lines:
    #         part = line.partition(" : ")
    #         msg1 = part[0]
    #         msg2 = part[2]
