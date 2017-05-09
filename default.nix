with import <nixpkgs> {}; 

stdenv.mkDerivation {
    name = "petanqulator";
    buildInputs = [ stdenv tup bullet xorg.libXmu pkgconfig mesa_glu gnome2.gtkglextmm gnome2.gtkmm xorg.libxcb xorg.libpthreadstubs ];
    src = ./.;
    configurePhase = ''
        mkdir -p $out/build_tup/petanqulator
        mkdir -p $out/build_tup/petanqulator_cli
        mkdir -p $out/build_tup/petanqulator_gui
        substituteInPlace Tupfile --replace "build_tup" "$out/build_tup"
        tup generate script.sh
    '';
    buildPhase = ''
        ./script.sh
    '';
    installPhase = ''
        mkdir -p $out/bin
        cp $out/build_tup/*.out $out/bin/
   '';
}

