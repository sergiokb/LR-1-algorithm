# LR-1-algorithm

This is a realisation of LR(1) parser.       
*Input* - LR(1) grammar and list of words to check    
*Output* - list of answers:    
**NO**, if the word doesn't belong to the grammar,    
**YES**, if it belongs, and in that case - parsing of it.    

### About running
#### For your own test  :
Run *main.cpp*, having your grammar in *grammar.txt* and input words in *words.txt*

Format of grammar.txt:
```
Starting with: S
1. S -> SaSb
2. S -> $
```

Format of words.txt:
```
abba
aabb
```

Answer in this case:
```
YES 22211
NO
```

Note that **epsilon** should be written as **$**
#### For checking my tests:

Run *my_tests.cpp*
