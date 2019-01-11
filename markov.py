import re
from numpy.random import choice
import os

def train_markov(filename, markov_mat):
	words = []
	word_reg = re.compile(r"^[a-z'’\ -]+$", re.IGNORECASE)
	try:
		f = open(filename, 'r', errors='replace')
		words = f.read().split('\n')
		words = list(filter(lambda x: word_reg.match(x) != None, words))
		f.close()
		
	except IOError:
		print('IO error: File '+ filename +' doesn\'t exist')
		exit
		
	chars_used = list(set([char for word in words for char in word]))
	if markov_mat == None:
		markov_mat = {chars_used[i]:{chars_used[i]:0 for i in range(len(chars_used))} for i in range(len(chars_used))}
	
	for word in words:
		for i in range(len(word) -1):
			markov_mat[word[i]][word[i+1]] += 1
			
	for a in chars_used:
		tot = sum(markov_mat[a].values())
		for b in chars_used:
			if tot:
				markov_mat[a][b] /= tot
			else:
				markov_mat[a][b] = 1/len(chars_used)
	return markov_mat
def succ(char):
	return choice(list(markov_mat[char].keys()), 1, p=list(markov_mat[char].values()))[0]

def gen_word(start, max_length):
	if start not in chars_used:
		return ''
	res = ''
	i = 0
	while start != '\n' and i < max_length:
		res += start
		i += 1
		start = succ(start)
	return res

directory = './exclastxt'
files = os.listdir(directory)

markov_mat = None
for i in files:
	markov_mat = train_markov(directory+'/'+i, markov_mat)

print('trained with',len(files),'books')
chars_used = markov_mat.keys()
print(gen_word('T', 200))


