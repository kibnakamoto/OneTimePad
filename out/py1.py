ord_w0 = ["mil", "sm", "af", "ep", "ife", "el", "as", "A", "etw", "if", "ia", "tc", "fa", "ga", "lk", "at", "ck", "lw", "of", "pu", "nc", "tc", "mi", "wi", "of", "is", "os", "se", "ig", "ga", "te", "ag", "rg", "A"]
ord_w1 = ["say", "me", "is", "me", "ask", "my", "if", "I", "may", "as", "at", "am", "so", "is", "by", "of", "my", "be", "at", "is", "we", "me", "to", "no", "is", "of", "if", "up", "or", "at", "am", "to", "go", "I"]
f = open("out/output1.txt", "w")
for i0 in range(1, 10):
	for i1 in range(10, 12):
		for i2 in range(12, 18):
			for i3 in range(18, 23):
				for i4 in range(23, 29):
					for i5 in range(29, 32):
						for i6 in range(32, 33):
							tmp = ord_w0[i0] + ord_w0[i1] + ord_w0[i2] + ord_w0[i3] + ord_w0[i4] + ord_w0[i5] + ord_w0[i6] + " : " + ord_w1[i0] + ord_w1[i1] + ord_w1[i2] + ord_w1[i3] + ord_w1[i4] + ord_w1[i5] + ord_w1[i6]
							f.write(tmp + "\n")
							print(tmp)
f.close()
