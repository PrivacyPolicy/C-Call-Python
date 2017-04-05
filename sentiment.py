#import sentimentweb.info as s
#from s import MyDict
#import sentimentweb.info.MyDict as d
#from sentimentweb.info import MyDict, feature_selection_trials, classify2

from sentimentweb.info import feature_selection_trials, MyDict, classify2

#text = 'Good afternoon. My name is Russel, and I\'m a senior wilderness explorer. Are you in need of any assistance today, Sir?'
#text2 = 'I hate this person with a passion, so I couldn\'t enjoy the movie'

def analyze(text):
    #from sentimentweb.info import feature_selection_trials
    #from sentimentweb.info import MyDict
    #t = MyDict()
    #print(t)
    feature_selection_trials()
    #print(classify2(text))
    #print(classify2(text2))
    #print(classify2(text3))
    #value = classify2(text3)
    #return {
    #    'sentiment': 'positive' if value[0] else 'negative',
    #    'certainty': value[1]
    #}
    return classify2(text)

#def main():
#    analyze("Hi there, my name is a name of happy happy happy.")
#
#main()
