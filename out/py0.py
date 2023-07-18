ord_w0 = ["mil", "sm", "af", "ep", "ife", "el", "as", "A", "etw", "if", "ia", "tc", "fa", "ga", "lk", "at", "ck", "lw", "of", "pu", "nc", "tc", "mi", "wi", "of", "is", "os", "se", "ig", "ga", "te", "ag", "rg", "A"]
ord_w1 = ["say", "me", "is", "me", "ask", "my", "if", "I", "may", "as", "at", "am", "so", "is", "by", "of", "my", "be", "at", "is", "we", "me", "to", "no", "is", "of", "if", "up", "or", "at", "am", "to", "go", "I"]
f = open("out/output0.txt", "w")
for i0 in range(0, 9):
	for i1 in range(9, 11):
		for i2 in range(11, 17):
			for i3 in range(17, 22):
				for i4 in range(22, 28):
					for i5 in range(28, 31):
						for i6 in range(31, 32):
							tmp = ord_w0[i0] + ord_w0[i1] + ord_w0[i2] + ord_w0[i3] + ord_w0[i4] + ord_w0[i5] + ord_w0[i6] + " : " + ord_w1[i0] + ord_w1[i1] + ord_w1[i2] + ord_w1[i3] + ord_w1[i4] + ord_w1[i5] + ord_w1[i6]
							f.write(tmp + "\n")
							print(tmp)
f.close()
