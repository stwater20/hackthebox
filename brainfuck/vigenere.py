plaintext = "OrestisHackingforfunandprofit"
ciphertext = "PieagnmJkoijegnbwzwxmlegrwsnn"
key = ""
for i in range(len(plaintext)):
	num_key = ((ord(ciphertext[i]) - ord(plaintext[i])) % 26) + 97
	char_key = chr(num_key)
	key = key + char_key
print(key)
