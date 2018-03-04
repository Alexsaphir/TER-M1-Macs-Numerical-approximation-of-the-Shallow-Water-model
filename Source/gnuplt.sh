for i in  out-*
do
	#echo "$i"
	gnuplot -e "set terminal png size 400,300; set output '$i.png';plot '$i' u 1:2 w l" 
	rm $i
done

#convert -delay 1 -loop 0 *.png Plot.gif

#ffmpeg -pattern_type glob -i "out-*.png" Output.mkv
ffmpeg -i "out-%d.png" Output.mkv
rm *.png
