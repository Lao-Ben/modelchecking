while read state color; do
         echo "/area_$state/ s/#D3D3D3/$color/";
done < graph.data > script.sed
echo "sed script done"
curl -s http://www.cs.cmu.edu/~bryant/boolean/US48_nocurves.svg | sed -f script.sed > colored.svg
echo "svg generation done"
