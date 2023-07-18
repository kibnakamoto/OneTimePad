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
with open("out/bigram_out.txt", "w") as f:
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
                                    if hx(onetimepad(string, string2))[ind] != m1m2[ind]:
                                        for i in range(256):
                                            if 32 ^ i == m1m2[ind]:
                                                string[ind] = ' '
                                                string2[ind] = i
                                                break
                                    if hx(onetimepad(string, string2))[ind+1] != m1m2[ind+1]:
                                        for i in range(256):
                                            if 32 ^ i == m1m2[ind+1]:
                                                string2[ind+1] = ' '
                                                string[ind+1] = i
                                                break
                                    ind = 1
                                    string[ind] = b1[i1][0]
                                    string[ind+1] = b1[i1][1]
                                    string2[ind] = b2[i1][0]
                                    string2[ind+1] = b2[i1][1]
                                    if hx(onetimepad(string, string2))[ind] != m1m2[ind]:
                                        for i in range(256):
                                            if 32 ^ i == m1m2[ind]:
                                                string[ind] = ' '
                                                string2[ind] = i
                                                break
                                    if hx(onetimepad(string, string2))[ind+1] != m1m2[ind+1]:
                                        for i in range(256):
                                            if 32 ^ i == m1m2[ind+1]:
                                                string2[ind+1] = ' '
                                                string[ind+1] = i
                                                break
                                    ind = 2
                                    string[ind] = b1[i2][0]
                                    string[ind+1] = b1[i2][1]
                                    string2[ind] = b2[i2][0]
                                    string2[ind+1] = b2[i2][1]
                                    if hx(onetimepad(string, string2))[ind] != m1m2[ind]:
                                        for i in range(256):
                                            if 32 ^ i == m1m2[ind]:
                                                string[ind] = ' '
                                                string2[ind] = i
                                                break
                                    if hx(onetimepad(string, string2))[ind+1] != m1m2[ind+1]:
                                        for i in range(256):
                                            if 32 ^ i == m1m2[ind+1]:
                                                string2[ind+1] = ' '
                                                string[ind+1] = i
                                                break
                                    ind = 3
                                    string[ind] = b1[i3][0]
                                    string[ind+1] = b1[i3][1]
                                    string2[ind] = b2[i3][0]
                                    string2[ind+1] = b2[i3][1]
                                    if hx(onetimepad(string, string2))[ind] != m1m2[ind]:
                                        for i in range(256):
                                            if 32 ^ i == m1m2[ind]:
                                                string[ind] = ' '
                                                string2[ind] = i
                                                break
                                    if hx(onetimepad(string, string2))[ind+1] != m1m2[ind+1]:
                                        for i in range(256):
                                            if 32 ^ i == m1m2[ind+1]:
                                                string2[ind+1] = ' '
                                                string[ind+1] = i
                                                break
                                    ind = 6
                                    string[ind] = b1[i4][0]
                                    string[ind+1] = b1[i4][1]
                                    string2[ind] = b2[i4][0]
                                    string2[ind+1] = b2[i4][1]
                                    if hx(onetimepad(string, string2))[ind] != m1m2[ind]:
                                        for i in range(256):
                                            if 32 ^ i == m1m2[ind]:
                                                string2[ind] = ' '
                                                string[ind] = i
                                                break
                                    if hx(onetimepad(string, string2))[ind+1] != m1m2[ind+1]:
                                        for i in range(256):
                                            if 32 ^ i == m1m2[ind+1]:
                                                string2[ind+1] = ' '
                                                string[ind+1] = i
                                                break
                                    ind = 10
                                    string[ind] = b1[i5][0]
                                    string[ind+1] = b1[i5][1]
                                    string2[ind] = b2[i5][0]
                                    string2[ind+1] = b2[i5][1]
                                    if hx(onetimepad(string, string2))[ind] != m1m2[ind]:
                                        for i in range(256):
                                            if 32 ^ i == m1m2[ind]:
                                                string[ind] = ' '
                                                string2[ind] = i
                                                break
                                    if hx(onetimepad(string, string2))[ind+1] != m1m2[ind+1]:
                                        for i in range(256):
                                            if 32 ^ i == m1m2[ind+1]:
                                                string[ind+1] = ' '
                                                string2[ind+1] = i
                                                break
                                    ind = 11
                                    string[ind] = b1[i6][0]
                                    string[ind+1] = b1[i6][1]
                                    string2[ind] = b2[i6][0]
                                    string2[ind+1] = b2[i6][1]
                                    if hx(onetimepad(string, string2))[ind] != m1m2[ind]:
                                        for i in range(256):
                                            if 32 ^ i == m1m2[ind]:
                                                string[ind] = ' '
                                                string2[ind] = i
                                                break
                                    if hx(onetimepad(string, string2))[ind+1] != m1m2[ind+1]:
                                        for i in range(256):
                                            if 32 ^ i == m1m2[ind+1]:
                                                string2[ind+1] = ' '
                                                string[ind+1] = i
                                                break
                                    strings = "\"" + ''.join(i for i in string) + "\" : \"" + ''.join(i for i in string2) + "\""
                                    print(strings)
                                    f.write(strings + "\n")
                                    print(hx(onetimepad(string, string2)), " : " , m1m2)
                                    exit()