from sentimentweb.info import MyDict, classify2, feature_selection_trials

text = 'Good afternoon. My name is Russel, and I\'m a senior wilderness explorer. Are you in need of any assistance today, Sir?'
text2 = 'I hate this person with a passion, so I couldn\'t enjoy the movie'

def main():
    print(feature_selection_trials())
    print(classify2(text))
    print(classify2(text2))

main()
