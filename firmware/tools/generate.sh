for freq in 80 #100 120 140 160 180 200 220 240 250 260
do
  ./icepll -i 48 -o ${freq} -m -f ./module_pll_${freq}M.v
  sed -i -e "s/module pll/module pll_{freq}/g" ./module_pll_${freq}M.v
  rm ./module_pll_${freq}M.v-e
done
