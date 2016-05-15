with import <nixpkgs> {}; 

stdenv.mkDerivation {
    name = "petanqulator";
    buildInputs = [ stdenv cmake bullet pkgconfig mesa_glu gtkmm ];
    src = ./.;
}

