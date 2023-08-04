# OneTimePad


Why you shouldn't use the same key twice when using One time pad encryption scheme. 

This tool is also a really good password generator. Remember two catch-phrases, these catch-phrases can generate even millions of passwords and if the catch-phrase is private, no one else can figure them out. It is kind of like hashing. Also remember a linenumber so you know which sentence it is. Only that one catch phrase can generate that specific sentence. Longer the catch-phrase, longer the password, less meaningful words in the catch-phrase, the more gibberish the password.

Rather than cracking a human readable sentence, this tool is more suitable for cracking passwords

But, if you give more data, rather than use the current arrays of data (bigrams, trigrams, words), add custom data. It can be more accurate.

Code is designed for Linux (Ubuntu) & Unix based OSs. Will not work on Windows.

Enter two sentences of the same length. They are encrypted using a random key and then the code tries bigrams, trigrams, and a list of over 300 words to find all the possible combinations. There are possible sentences generated into an output file (There can be multiple if there was a need for multiple threads), then the possible sentences are added into a file. If you don't want to see these possible sentences (They aren't accurate), type (n)o after the code is finished.

if the output#.txt files don't satisfy you, try running the cracker.py in python3 generate possible sentences that satisfy the ```m1 xor m2 = m1m2```. The output
## To Generate Possible Sentences Using Bigrams

First compile \& run twiceuse.cpp with the data you want
``` sh compile && ./twice 1 ``` the 1 is optional, it is too see what certain sentences can combine to be, and to remove certain values ORD_W (word combinations).

twice generates all the required data in the out folder, then run cracker to generate sentences using bigrams. The bigrams are generated in ```twice``` to the file ```out/bigrams.txt```

to run cracker:
```
python3 cracker.py
```

The bigram sentences are saved in ```out/bigram_out.txt```

### m1m2: m1m2 is the sentence 1 you enter xored by the sentence 2 you entered in the ```twice``` UI.

Basically equal to ciphertext 1 xor ciphertext 2 and 
equal to plaintext 1 xor plaintext 2.

This is the vulnurability of the OneTimePad. This is still really hard to crack because there are near unlimited combinations that can work out.

When running the program, if we asume that the executable name is ```twice```, then run it using ```./twice 1``` for a CLI on deleting certain values off the word list and seeing some combinations. These are also not a 100% accurate but they can give you an idea


## How to calculate all the sentences
```
import sys
def onetimepad(x:str,y:str) -> str:
    ret = ""
    for i in range(len(x)):
        ret += chr(ord(x[i]) ^ ord(y[i]))
    return ret

def hx(x):
    ret = []
    for i in x:
        ret.append(hex(ord(i))[2:].zfill(2))
    return ret

b1 = ['lm', 'pl', 'po', 'rm', 'sm', 'la', 'ia', 'af', 'ig', 'fa', 'fr', 'if', 'ep', 'lp', 'av', 'af', 'ag', 'ak', 'ck', 'ga', 'po', 'of', 'at', 'ga', 'ag', "'s", 'mo', 'pu', 'xt', 'mi', 'wr', 'wa', 'uc', 'tc', 'ki', 'pe', 'ga', 'ig', 'is', 'of', 'ha', 'hr', 'up', 'nt', 'ov', 'ct', 'ep', 'am', 'pl', 'ag', 'ga', 'pi']
b2 = ['re', 'nd', 'ng', 'le', 'me', 'ri', 'at', 'is', 'ar', 'nt', 'ng', 'as', 'me', 'de', 'ic', 'th', 'ti', 'te', 've', 'ro', 'ea', 'at', 'of', 'is', 'ou', 'nt', 'ti', 'is', 'ar', 'to', 'nt', 'ng', 'le', 'me', 'ro', 'ic', 'at', 'or', 'of', 'is', 'nt', 'ng', 'se', 'ha', 'ic', 'ea', 'ce', 'te', 'ed', 'to', 'ri', 'ea']
m1m2=['1e', '08', '15', '0e', '12', '53', '49', '07', '4e', '4e', '19', '06', '15', '08', '00']
with open("out/bigram_out.txt", "w+") as f:
    for i0 in range(0, 6):
        for i1 in range(6, 15):
            for i2 in range(15, 21):
                for i3 in range(21, 25):
                    for i4 in range(25, 26):
                        for i5 in range(26, 36):
                            for i6 in range(36, 47):
                                for i7 in range(47, 52):
                                    string = list(" "*15)
                                    string2 = list(" "*15)
                                    ind = 0
                                    string[ind] = b1[i0][0]
                                    string[ind+1] = b1[i0][1]
                                    string2[ind] = b2[i0][0]
                                    string2[ind+1] = b2[i0][1]
                                    ind = 1
                                    string[ind+1] = b1[i1][1]
                                    string2[ind+1] = b2[i1][1]
                                    ind = 2
                                    string[ind+1] = b1[i2][1]
                                    string2[ind+1] = b2[i2][1]
                                    ind = 3
                                    string[ind+1] = b1[i3][1]
                                    string2[ind+1] = b2[i3][1]
                                    ind = 6
                                    string[ind] = b1[i4][0]
                                    string2[ind] = b2[i4][0]
                                    string[ind+1] = b1[i4][1]
                                    string2[ind+1] = b2[i4][1]
                                    ind = 10
                                    string[ind] = b1[i5][0]
                                    string2[ind] = b2[i5][0]
                                    string[ind+1] = b1[i5][1]
                                    string2[ind+1] = b2[i5][1]
                                    ind = 11
                                    string[ind+1] = b1[i6][1]
                                    string2[ind+1] = b2[i6][1]
                                    ind = 12
                                    string[ind+1] = b1[i7][1]
                                    string2[ind+1] = b2[i7][1]
                                    for ind in range(15):
                                        while hx(onetimepad(string, string2))[ind] != m1m2[ind]:
                                            number = 32
                                            for i in range(97,122):
                                                if number ^ i == int(m1m2[ind], 16):
                                                    string2[ind] = chr(number)
                                                    string[ind] = chr(i)
                                                    break
                                    strings = "\"" + ''.join(i for i in string) + "\" : \"" + ''.join(i for i in string2) + "\""
                                    f.write(strings + "\n")
                                inc+=1
```
```inc``` should equal the total amount of sentence combinations:

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

The py# files are created by twice. While bigram.py is created by running cracker.py. Bigram.py generates better output but they both satisfy the ```m1 xor m2 = m1m2```.

In some sentences, there might be a lot of gibberish data. This is filling made to satisfy the equation, to get rid of it, run ```twice``` or ```cracker.py``` with ```--no-fill```

Setting no-fill results in ```m1 xor m2 = m1m2``` no longer being satisfied because the fill is for unknown digits of the sentence. Except, you can fill the data yourself. All the spacebars are unknowns to be filled. This code fills string2 with ' ' (ascii 32) and string with a number between 97,122 that results satisfying ```m1 xor m2 = m1m2```. A code like this can be used for filling:
```
\# assuming onetimepad and m1m2 are a hex bytearray/list where each ind are 1 byte
\# string and string2 are each a sentence
for ind in range(len(m1m2)):
    while onetimepad(string, string2)[ind] != m1m2[ind]:
        number = 32 # ascii equvilent of ' '
        for i in range(97,122):
            if number ^ i == int(m1m2[ind], 16):
                string2[ind] = chr(number)
                string[ind] = chr(i)
                break
```

NOTE: if the code is never ending (if cracker.py isn't writing to out/bigram_out.txt or if twiceuse.cpp generated out/py#.py files aren't generating data into out/output#.txt), than try to run using --no-fill because there is a possibility that there is no filling possible. Then, the data will not satisfy ```m1 xor m2 = m1m2``` but it will not be stuck in an endless loop. Another thing you can try is to assign number (cracker.py:162) to random.randrange(97,122) for letters only, or set to something like secrets.randbelow(256) for all characters. And assign number in (twiceuse.cpp:289) to randrange(0,256) or set (twiceuse.cpp:290) loop range(97,122) to range(256).

If the values provided are already set, then there might not be an endless loop, try a shorter message.
