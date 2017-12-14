# Boggle-Word-Finder

This is a Boggle board generator and word finder.
The program generates letters with a non-uniform weights to a produce a word-friendly board for playing.
A recursive function tests all possible word sequences and stores valid words in a .txt file.
Quick runtime, despite recursive algorithm due to constant checking if letter sequence is still valid. This drastically cuts down the search time.

Note: The .txt file contains the English words database. You can replace that file with a database for French words as well, just make sure to rename it to: corncob_lowercase.txt
