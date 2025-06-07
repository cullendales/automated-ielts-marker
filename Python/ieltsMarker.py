
from spellchecker import SpellChecker
import sys
import docx2txt
import string
from collections import Counter
import nltk
from nltk.corpus import wordnet

nltk.download('wordnet')

# checks how many paragraphs are in the ielts paper
def structure(paper):
    
    paper = paper.lstrip()
  
    count = 0
    count = paper.count('\n\n') + 1
    
    if count < 4:
        print('You only wrote', count, 'paragraphs. This is not enough to obtain a high IELTS score.')
        print('Please make sure you write exactly 4 paragraphs in the future.')
        
    if count == 4:
        print('Great paragraph structure. 4 paragraphs is perfect. Good job!')
        
    if count > 4:
        print("You wrote", count, 'paragraphs. Please write only 4 in the future.')
    
    return count
  
    
# list number of incorrect words spelt
def spellCheck(words):
    
    spell = SpellChecker(language = 'en')
        
    misspelled = spell.unknown(words)
    
    num = len(misspelled)
    
    for i in misspelled:
        print('Incorrect word:', i, 'Most likely correction:', spell.correction(i), 'Possible correct spelling:', spell.candidates(i))
              
    return num
 
    
# - better word choice (very smth ie sad - morose,; very bad - terrible)
def wordChoice(words):
    
    count = 0
    
    simple_words = {
        'bad': ['poor', 'unacceptable', 'inferior', 'subpar'],
        'good': ['excellent', 'outstanding', 'superb', 'remarkable'],
        'happy': ['joyful', 'content', 'delighted', 'cheerful'],
        'sad': ['unhappy', 'sorrowful', 'mournful', 'dejected'],
        'big': ['large', 'huge', 'immense', 'massive'],
        'small': ['tiny', 'minuscule', 'petite', 'compact'],
        'smart': ['intelligent', 'clever', 'brilliant', 'wise'],
        'dumb': ['foolish', 'unwise', 'ignorant', 'obtuse'],
        'nice': ['pleasant', 'agreeable', 'friendly', 'kind'],
        'mean': ['cruel', 'unkind', 'harsh', 'malicious'],
        'pretty': ['beautiful', 'gorgeous', 'stunning', 'lovely'],
        'ugly': ['unattractive', 'unsightly', 'hideous', 'unpleasant'],
        'fast': ['quick', 'speedy', 'swift', 'rapid'],
        'slow': ['sluggish', 'lethargic', 'unhurried', 'delayed'],
        'easy': ['simple', 'effortless', 'straightforward', 'uncomplicated'],
        'hard': ['difficult', 'challenging', 'tough', 'demanding'],
        'rich': ['wealthy', 'affluent', 'prosperous', 'well-off'],
        'poor': ['impoverished', 'destitute', 'underprivileged', 'needy'],
        'fun': ['enjoyable', 'entertaining', 'amusing', 'delightful'],
        'boring': ['dull', 'tedious', 'monotonous', 'uninteresting'],
        'strong': ['powerful', 'robust', 'mighty', 'sturdy'],
        'weak': ['frail', 'feeble', 'fragile', 'delicate'],
        'tired': ['exhausted', 'weary', 'fatigued', 'drained'],
        'angry': ['furious', 'irate', 'incensed', 'livid'],
        'scared': ['afraid', 'frightened', 'terrified', 'alarmed'],
        'surprised': ['astonished', 'amazed', 'shocked', 'astounded'],
        'interesting': ['fascinating', 'captivating', 'intriguing', 'engaging'],
        'hardworking': ['diligent', 'industrious', 'dedicated', 'assiduous']}
  
    # the word replacements for words with very in front
    very_words = { 
        'bad': ['terrible', 'awful', 'dreadful', 'horrendous'],
        'good': ['excellent', 'superb', 'outstanding', 'remarkable'],
        'happy': ['ecstatic', 'joyful', 'elated', 'thrilled'],
        'sad': ['heartbroken', 'miserable', 'sorrowful', 'devastated'],
        'big': ['huge', 'immense', 'massive', 'enormous'],
        'small': ['tiny', 'minuscule', 'microscopic', 'petite'],
        'smart': ['brilliant', 'genius', 'intelligent', 'sharp'],
        'dumb': ['foolish', 'ignorant', 'mindless', 'dim-witted'],
        'nice': ['charming', 'pleasant', 'gracious', 'delightful'],
        'mean': ['cruel', 'malicious', 'vindictive', 'vicious'],
        'pretty': ['gorgeous', 'stunning', 'beautiful', 'radiant'],
        'ugly': ['hideous', 'unsightly', 'repulsive', 'grotesque'],
        'fast': ['rapid', 'swift', 'quick', 'speedy'],
        'slow': ['sluggish', 'lethargic', 'plodding', 'delayed'],
        'easy': ['effortless', 'simple', 'painless', 'straightforward'],
        'hard': ['challenging', 'arduous', 'demanding', 'formidable'],
        'rich': ['wealthy', 'affluent', 'prosperous', 'well-off'],
        'poor': ['destitute', 'impoverished', 'needy', 'penniless'],
        'fun': ['exciting', 'enjoyable', 'amusing', 'delightful'],
        'boring': ['tedious', 'monotonous', 'dreary', 'mind-numbing'],
        'strong': ['powerful', 'formidable', 'sturdy', 'robust'],
        'weak': ['fragile', 'frail', 'feeble', 'delicate'],
        'tired': ['exhausted', 'weary', 'fatigued', 'drained'],
        'angry': ['furious', 'irate', 'incensed', 'livid'],
        'scared': ['terrified', 'petrified', 'alarmed', 'fearful'],
        'surprised': ['astonished', 'astounded', 'amazed', 'shocked'],
        'interesting': ['fascinating', 'captivating', 'intriguing', 'engrossing'],
        'hardworking': ['diligent', 'industrious', 'dedicated', 'assiduous'],
        'clean': ['spotless', 'immaculate', 'pristine', 'untarnished'],
        'dirty': ['filthy', 'grimy', 'squalid', 'unclean']
    }
    
    # checks to see if word found has 'very' in front and if so, then chooses the 'very' list for word correction
    word = 0       
    while word < len(words)-1:
        if words[word] == 'very':
            if words[word+1] in very_words:
                word +=1
                print('You used the word: Very', words[word], ' - Some better choices are: ', very_words[words[word]])
                count+=1
        elif words[word] in simple_words:
                print('You used the word: ', words[word], ' - Some better choices are: ', simple_words[words[word]])
                count+=1
        word+=1
           
    return count

    
# things done well (ie conjunctions, good amount of sentences)
def thingsDoneWell(words):
    good_word_count = 0
    
    conjunctions = {"accordingly", "after", "also", "before", "besides", "consequently", "conversely", "finally", 
                    "furthermore", "hence", "however", "indeed", "instead", "likewise", "meanwhile", "moreover", 
                    "nevertheless", "next", "nonetheless", "otherwise", "similarly", "still", "subsequently", 
                    "then", "therefore", "thus"}
    
    good_vocab = {"noteworthy", "detrimental", "beneficial", "predominantly", "fundamental", "allocate", "emphasize", 
                  "comprise", "mitigate", "implement", "controversial", "perspective", "advocate", "assert", "refute", 
                  "endorse", "imply", "justify", "undermine", "substantiate", "induce", "engender", "catalyst", 
                  "precipitate", "exacerbate", "contribute", "stifle", "impede", "generate", "perpetuate", "escalate", 
                  "fluctuate", "diminish", "transform", "proliferate", "adapt", "decline", "prevail", "diversify", 
                  "stabilize", "superior", "inferior", "analogous", "comparable", "distinct", "contrasting", "parallel", 
                  "variant", "analogous", "contradictory", "in summary", "ultimately", "in essence", "conclude", 
                  "in light of", "in retrospect", "taking into account", "on balance", "overall", "to reiterate", 
                  "accumulate", "allocate", "appreciate", "assess", "attain", "circumvent", "coerce", "collaborate", 
                  "compile", "consolidate", "decipher", "defer", "delegate", "devise", "dominate", "elaborate", 
                  "enhance", "expedite", "facilitate", "formulate", "implement", "initiate", "integrate", "intervene", 
                  "legitimize", "mandate", "optimize", "perceive", "preserve", "prioritize", "propagate", "rectify", 
                  "regulate", "replicate", "restrict", "revamp", "simulate", "streamline", "surpass", "sustain", 
                  "validate", "viable", "equitable", "vibrant", "plummet", "saturate", "strive", "sporadic", "imperative", 
                  "resilience", "prevalent", "augment", "affluent", "proficient", "plausible", "rigorous", "imminent", 
                  "predicament", "profound", "pivotal", "repercussion", "escalate"}

    
    for word in words:
        if word in conjunctions:
            good_word_count +=1.5
            
    for word in words:
        if word in good_vocab:
            good_word_count +=1
               
    return good_word_count

 
# checks to see if a word is overused
def wordOveruse(words):
    
    count = 0
    
    common_words = {
            "the", "be", "to", "of", "and", "a", "in", "that", "have", "I",
            "it", "for", "not", "on", "with", "he", "as", "you", "do", "at",
            "this", "but", "his", "by", "from", "they", "we", "say", "her", "she",
            "or", "an", "will", "my", "one", "all", "would", "there", "their", "what",
            "so", "up", "out", "if", "about", "who", "get", "which", "go", "me",
            "when", "make", "can", "like", "time", "no", "just", "him", "know", "take",
            "people", "into", "year", "your", "good", "some", "could", "them", "see", "other",
            "than", "then", "now", "look", "only", "come", "its", "over", "think", "also",
            "back", "after", "use", "two", "how", "our", "work", "first", "well", "way",
            "even", "new", "want", "because", "any", "these", "give", "day", "most", "us", 'is',
            'was', 'will', 'are'}
    
    words_copy = words[:]
    
    for word in words_copy[:]:
        if word in common_words:
            words_copy.remove(word)
            
    word_count = Counter(words_copy)
    
    print('Word Repetition:')
    for i in word_count:
        if word_count[i] >= 4:
            print('The word', i,'was used', word_count[i], 'times')
            count +=1
     
    return count   


# determines wordcount and impact on mark from this value
def wordCount(seperate_words):
       
    numWords = len(seperate_words)
    print('Word Count:', numWords)
    
    # categorizes how many words are in the paper and can be later used to help determine mark
    if numWords < 100:
        numWords_value = 1
        
    elif numWords >= 100 and numWords <= 150:
          numWords_value = 2
          
    elif numWords > 150 and numWords <= 200:
           numWords_value = 3
    
    elif numWords > 200 and numWords < 250:
          numWords_value = 4
    
    elif numWords >= 250 and numWords <= 350:
          numWords_value = 5
          
    elif numWords > 350 and numWords <= 450:
          numWords_value = 6
          
    else:
          numWords_value = 7
                     
    return numWords, numWords_value

# tallies up final ielts score using values obtained from other methods
def ieltsScore(numWords_value, num_misspelled, overuse_score, structure_score, good_num, score_wc):
       
    if numWords_value < 4:
        score = 5
        print('Please write more in the future. You must write a minimum of 250 words.')
    
    elif numWords_value == 4:
        score = 6
        print('You almost wrote enough. Please write more in the future. You must write a minimum of 250 words.')
        
    elif numWords_value == 5:
        score = 6.75
        
    elif numWords_value >= 6:
        score = 6.5
        print('You wrote too much. More is not better. Please try to write only 250 - 300 words in the future.')
        
    if num_misspelled >= 2 and num_misspelled <= 3:
        score -= 0.25
        
    elif num_misspelled > 3 and num_misspelled < 6:
        score -= 0.5
        print('You made ', num_misspelled, ' spelling mistakes. Please check your spelling more carefully after finishing your essay.')
        
    elif num_misspelled > 6:
        score -= 1
        print('You made ', num_misspelled, ' spelling mistakes. Please check your spelling more carefully after finishing your essay.')
        
    if overuse_score == 2:
        score -= 0.25
        
    elif overuse_score >= 3 and overuse_score <= 4:
        score -= 0.5
        
    elif overuse_score > 4:
        score -= 0.75
        
    if structure_score < 4:
        score -= 1
    
    elif structure_score > 4:
        score -= 0.75
    
    if good_num >= 5 and good_num <= 6:
        score += 0.25
    
    elif good_num > 6 or good_num <= 7:
        score += 0.5
        
    elif good_num > 7:
        score += 0.75
        
    if score_wc < 2:
        score += 0.25
        
    if score_wc > 6:
        score -= 0.25
        print('You reused many simple words in your essay. Please try to use more advanced vocabulary in your essay for a higher score.')
   
    return score
    

def main():

    # loads ielts paper
    ielts = sys.argv[1]
    paper = docx2txt.process(ielts)
    
    # checks to see if student included question and eliminates it
    task_2_question = 'Write at least 250 words'
    find_t2q = paper.find(task_2_question)
    
    if find_t2q != -1:      
        paper = paper[find_t2q + 24:]
                
    # seperate words and clean them
    no_punc = paper.translate(str.maketrans('', '', string.punctuation))
    words = no_punc.split()
    
    
    # call methods to get scores for each section of the paper
    numWords, numWords_value = wordCount(words)     
    num_misspelled = spellCheck(words)   
    overuse_score = wordOveruse(words)   
    good_num = thingsDoneWell(words) 
    structure_score = structure(paper)  
    wc_score = wordChoice(words)    

    # tally up final score using the scores obtained from the functions
    final_score = ieltsScore(numWords_value, num_misspelled, overuse_score, structure_score, good_num, wc_score)
    
    # checks to see if score is in between two ielts scores and outputs that range
    str_score = str(final_score)
    middle_score = 25
    upper_middle = 75
    str_middle = str(middle_score)
    str_upper_middle = str(upper_middle)
    
    if str_middle in str_score or str_upper_middle in str_score:
        print('Your IELTS score is: ', final_score - 0.25, '-', final_score + 0.25)
    else:
        print('Your IELTS score is: ', final_score)
    
if __name__ == '__main__':
    main()
