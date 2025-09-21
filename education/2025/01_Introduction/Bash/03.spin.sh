# Simple spinning cursor
spin='-\|/'
for i in {1..100}; do
  printf "\r%s" "${spin:i%4:1}"
  sleep 0.1
done
echo