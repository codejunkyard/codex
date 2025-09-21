secret=$(( RANDOM % 10 + 1 ))
echo "Guess a number between 1 and 10:"
read guess
if [[ $guess -eq $secret ]]; then
  echo "Correct! 🎉"
else
  echo "Wrong! The number was $secret"
fi