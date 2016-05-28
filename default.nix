with import <nixpkgs> {}; 

stdenv.mkDerivation {
    name = "petanqulator";
    buildInputs = [ stdenv cmake bullet xorg.libXmu pkgconfig mesa_glu gnome.gtkglextmm gnome.gtkmm xorg.libxcb xorg.libpthreadstubs ];
    src = ./.;
}

