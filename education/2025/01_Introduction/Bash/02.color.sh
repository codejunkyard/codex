echo -e "\e[31mRed\e[0m \e[32mGreen\e[0m \e[34mBlue\e[0m"

for i in {31..36}; do
  echo -e "\e[${i}mHello Bash!\e[0m"
done

