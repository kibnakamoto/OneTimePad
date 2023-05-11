# OneTimePad
Why you shouldn't use the same key twice when using One time pad encryption scheme. 

Code is designed for Linux (Ubuntu) & Unix based OSs. Will not work on Windows.

You enter two sentences of the same length. They are encrypted using a random key and then the code tries bigrams, trigrams, and a list of over 300 words to find all the possible combinations. There are possible sentences generated into an output file (There can be multiple if there was a need for multiple threads), then the possible sentences are added into a file. If you don't want to see these possible sentences (They aren't accurate), you can just type no after the code is finished.

When running the program, if we asume that the executable name is ```twice```, then run it using ```./twice 1``` for a CLI on deleting certain values off the word list and seeing some combinations. These are also not a 100% accurate but they can give you an idea

I have a vector for pieces of text. I need to combine them to make sentences of specified lengths. to make this possible. I need the following algorithm

## How to calculate all the sentences
```

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
                                inc+=1
```
```inc``` should equal the total amount of sentence combinations (268800):

```
inc = 1
for i in sizes:
    inc*=i
```


to evaluate sizes list, I have the following list.

e.g.   There are 4 ```0:``` values so ```sizes[0] = 4```. There are 7 ```1:``` values to ```sizes[1] = 7```...

```
[0: {ta, we}] [0: {na, me}] [0: {may, new}] [0: {new, may}] [1: {lk, he}] [1: {wa, so}] [1: {ik, me}] [1: {pa, to}] [1: {ca, go}] [1: {egi, air}] [1: {soun, want}] [2: {gh, is}] [2: {ov, am}] [2: {ou, an}] [2: {au, on}] [2: {it, go}] [2: {ai, or}] [2: {go, it}] [2: {oo, at}] [3: {ri, is}] [3: {rt, in}] [3: {ni, us}] [3: {top, out}] [3: {ou, to}] [3: {tt, on}] [3: {th, or}] [3: {rn, it}] [4: {sw, is}] [4: {ow, us}] [4: {ma, we}] [4: {ik, so}] [4: {wa, me}] [4: {nk, to}] [4: {xa, be}] [4: {ill, she}] [4: {ot, up}] [4: {sp, it}] [5: {ed, am}] [5: {eg, an}] [5: {ll, he}] [5: {il, me}] [5: {mo, if}] [6: {ht, am}] [7: {wr, no}] [7: {lm, up}] [7: {pi, it}] 

```
The numbers (0...,7) are for showing which string comes first, I cannot add 2 ```0``` strings to replicate the sentence.

the first sentence combination the algorithm needs to generate:

```ta-lk-gh-top-ow-ed-ht-wr : we-he-is-out-us-am-am-no```

Since the size of ```sizes``` is calculated at runtime and isn't always equal to 8, That's why there is python file(s) (py0.py) algorithm to create a nested loop for every ```sizes[i]```.
