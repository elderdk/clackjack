# clackjack
Game of single-deck blackjack made with C


Here are the steps:

1. You make a bet.
2. Dealer and you receive two cards. Dealer's second card is hidden.
3. You have three options:
    1) hit and receive one more card.
    2) stay and end your turn.
    3) double down on your original bet (X2), receive one more card and stay.

4. Dealer keeps receiving cards until dealer's score is 17 or higher.

You win if:
1. Your score is higher than the dealer.
2. Your score is 21 or less.
3. Your score is 21 immediately upon Round 1. (Called blackjack. This happens if you receive an Ace and a 10 card at the beginning of the game)
4. Dealer's score exceeds 21. (Dealer bust)

You lose if:
1. Your score is lower than the dealer.
2. Your score exceeds 21. (Player bust)

And tie (Push) if your and dealer's scores are same.

You can run the clackjack executable in the bin folder or you can compile it yourself using the Makefile.


Good luck!
