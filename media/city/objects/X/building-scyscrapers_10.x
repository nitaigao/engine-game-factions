xof 0303txt 0032
template XSkinMeshHeader {
 <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}

template VertexDuplicationIndices {
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}

template SkinWeights {
 <6f0d123b-bad2-4167-a0d0-80224f25fabb>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array FLOAT weights[nWeights];
 Matrix4x4 matrixOffset;
}

template FVFData {
 <b6e70a0e-8ef9-4e83-94ad-ecc8b0c04897>
 DWORD dwFVF;
 DWORD nDWords;
 array DWORD data[nDWords];
}

template EffectInstance {
 <e331f7e4-0559-4cc2-8e99-1cec1657928f>
 STRING EffectFilename;
 [...]
}

template EffectParamFloats {
 <3014b9a0-62f5-478c-9b86-e4ac9f4e418b>
 STRING ParamName;
 DWORD nFloats;
 array FLOAT Floats[nFloats];
}

template EffectParamString {
 <1dbc4c88-94c1-46ee-9076-2c28818c9481>
 STRING ParamName;
 STRING Value;
}

template EffectParamDWord {
 <e13963bc-ae51-4c5d-b00f-cfa3a9d97ce5>
 STRING ParamName;
 DWORD Value;
}


Material skyscrapers {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "Skyscrp.tga";
 }
}

Material buildz1 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "buildz1.tga";
 }
}

Material buildz3 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "buildz3.tga";
 }
}

Material buildz4 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "buildz4.tga";
 }
}

Material buildz5 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "buildz5.tga";
 }
}

Material buildz6 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "buildz6.tga";
 }
}

Material buildz2 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "buildz2.tga";
 }
}

Material roads {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "roads.tga";
 }
}

Material roads-2 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "roads2.tga";
 }
}

Material tree-01 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "trees-02.tga";
 }
}

Frame building-scyscrapers_10 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,-0.000000,-1.000000,0.000000,-0.000000,1.000000,-0.000000,0.000000,0.375810,-12.670539,8.976887,1.000000;;
 }

 Frame {
  

  FrameTransformMatrix {
   1.000000,-0.000000,0.000000,0.000000,-0.000000,1.000000,-0.000000,0.000000,0.000000,-0.000000,1.000000,0.000000,-0.000000,-0.000000,-0.000000,1.000000;;
  }

  Mesh  {
   108;
   -5.968900;10.979589;28.779205;,
   -12.661291;-5.881333;28.779205;,
   12.042380;-5.928021;28.774157;,
   -5.968899;10.979591;-0.000002;,
   -12.661291;-5.881334;-0.000002;,
   -12.661291;-5.881333;28.779205;,
   -12.661291;-5.881333;28.779205;,
   -5.968900;10.979589;28.779205;,
   -5.968899;10.979591;-0.000002;,
   -12.661291;-5.881334;-0.000002;,
   12.042381;-5.928022;-0.000002;,
   12.042380;-5.928021;28.774157;,
   12.042380;-5.928021;28.774157;,
   -12.661291;-5.881333;28.779205;,
   -12.661291;-5.881334;-0.000002;,
   12.042381;-5.928022;-0.000002;,
   -5.968899;10.979591;-0.000002;,
   -5.968900;10.979589;28.779205;,
   -5.968900;10.979589;28.779205;,
   12.042380;-5.928021;28.774157;,
   12.042381;-5.928022;-0.000002;,
   -5.052785;8.393194;105.187187;,
   -10.294718;-4.813419;105.187187;,
   9.054861;-4.849988;87.423050;,
   -10.294718;-4.813419;105.187187;,
   -5.052785;8.393194;105.187187;,
   -5.052785;8.393194;28.014900;,
   -5.052785;8.393194;28.014900;,
   -10.294718;-4.813419;28.014900;,
   -10.294718;-4.813419;105.187187;,
   9.054861;-4.849988;87.423050;,
   -10.294718;-4.813419;105.187187;,
   -10.294718;-4.813419;28.014900;,
   -10.294718;-4.813419;28.014900;,
   9.054862;-4.849988;28.014900;,
   9.054861;-4.849988;87.423050;,
   -5.052785;8.393194;105.187187;,
   9.054861;-4.849988;87.423050;,
   9.054862;-4.849988;28.014900;,
   9.054862;-4.849988;28.014900;,
   -5.052785;8.393194;28.014900;,
   -5.052785;8.393194;105.187187;,
   -0.369647;-5.719617;4.533180;,
   -0.378355;-10.145265;4.315884;,
   -10.369284;-10.123347;4.336219;,
   -10.369284;-10.123347;4.336219;,
   -10.360576;-5.697702;4.553515;,
   -0.369647;-5.719617;4.533180;,
   -0.369357;-5.713144;6.364285;,
   -10.360286;-5.691228;6.384620;,
   -10.369284;-10.123347;4.336219;,
   -10.369284;-10.123347;4.336219;,
   -0.378355;-10.145265;4.315884;,
   -0.369357;-5.713144;6.364285;,
   -10.360576;-5.697702;4.553515;,
   -10.369284;-10.123347;4.336219;,
   -10.360286;-5.691228;6.384620;,
   9.621280;-5.741534;4.512845;,
   9.612572;-10.167180;4.295548;,
   -0.378355;-10.145265;4.315884;,
   -0.378355;-10.145265;4.315884;,
   -0.369647;-5.719617;4.533180;,
   9.621280;-5.741534;4.512845;,
   9.621572;-5.735063;6.343949;,
   -0.369357;-5.713144;6.364285;,
   -0.378355;-10.145265;4.315884;,
   -0.378355;-10.145265;4.315884;,
   9.612572;-10.167180;4.295548;,
   9.621572;-5.735063;6.343949;,
   9.621280;-5.741534;4.512845;,
   9.621572;-5.735063;6.343949;,
   9.612572;-10.167180;4.295548;,
   -4.362432;6.333606;126.642349;,
   -8.379829;-3.787898;126.642349;,
   6.449622;-3.815924;108.878204;,
   -8.379829;-3.787898;126.642349;,
   -4.362432;6.333606;126.642349;,
   -4.362430;6.333605;85.955116;,
   -4.362430;6.333605;85.955116;,
   -8.379828;-3.787897;85.955116;,
   -8.379829;-3.787898;126.642349;,
   6.449622;-3.815924;108.878204;,
   -8.379829;-3.787898;126.642349;,
   -8.379828;-3.787897;85.955116;,
   -8.379828;-3.787897;85.955116;,
   6.449622;-3.815923;85.955116;,
   6.449622;-3.815924;108.878204;,
   -4.362432;6.333606;126.642349;,
   6.449622;-3.815924;108.878204;,
   6.449622;-3.815923;85.955116;,
   6.449622;-3.815923;85.955116;,
   -4.362430;6.333605;85.955116;,
   -4.362432;6.333606;126.642349;,
   -4.507123;-1.504869;122.718864;,
   -4.086718;-0.193179;122.718864;,
   -4.498460;-0.240240;153.589691;,
   -4.086718;-0.193179;122.718864;,
   -5.211828;-0.321370;122.718864;,
   -4.797815;-0.274347;153.589691;,
   -4.797815;-0.274347;153.589691;,
   -4.498460;-0.240240;153.589691;,
   -4.086718;-0.193179;122.718864;,
   -5.211828;-0.321370;122.718864;,
   -4.507123;-1.504869;122.718864;,
   -4.797815;-0.274347;153.589691;,
   -4.498460;-0.240240;153.589691;,
   -4.797815;-0.274347;153.589691;,
   -4.507123;-1.504869;122.718864;;
   36;
   3;0,1,2;,
   3;3,4,5;,
   3;6,7,8;,
   3;9,10,11;,
   3;12,13,14;,
   3;15,16,17;,
   3;18,19,20;,
   3;21,22,23;,
   3;24,25,26;,
   3;27,28,29;,
   3;30,31,32;,
   3;33,34,35;,
   3;36,37,38;,
   3;39,40,41;,
   3;42,43,44;,
   3;45,46,47;,
   3;48,49,50;,
   3;51,52,53;,
   3;54,55,56;,
   3;57,58,59;,
   3;60,61,62;,
   3;63,64,65;,
   3;66,67,68;,
   3;69,70,71;,
   3;72,73,74;,
   3;75,76,77;,
   3;78,79,80;,
   3;81,82,83;,
   3;84,85,86;,
   3;87,88,89;,
   3;90,91,92;,
   3;93,94,95;,
   3;96,97,98;,
   3;99,100,101;,
   3;102,103,104;,
   3;105,106,107;;

   MeshNormals  {
    108;
    0.000204;-0.000081;1.000000;,
    0.000204;-0.000081;1.000000;,
    0.000204;-0.000081;1.000000;,
    -0.929461;0.368919;-0.000000;,
    -0.929461;0.368919;-0.000000;,
    -0.929461;0.368919;-0.000000;,
    -0.929461;0.368919;-0.000000;,
    -0.929461;0.368919;-0.000000;,
    -0.929461;0.368919;-0.000000;,
    -0.001890;-0.999998;0.000000;,
    -0.001890;-0.999998;0.000000;,
    -0.001890;-0.999998;0.000000;,
    -0.001890;-0.999998;0.000000;,
    -0.001890;-0.999998;0.000000;,
    -0.001890;-0.999998;0.000000;,
    0.684416;0.729092;0.000000;,
    0.684416;0.729092;0.000000;,
    0.684416;0.729092;0.000000;,
    0.684416;0.729092;0.000000;,
    0.684416;0.729092;0.000000;,
    0.684416;0.729092;0.000000;,
    0.652913;-0.259153;0.711719;,
    0.652913;-0.259153;0.711719;,
    0.652913;-0.259153;0.711719;,
    -0.929461;0.368919;0.000000;,
    -0.929461;0.368919;0.000000;,
    -0.929461;0.368919;0.000000;,
    -0.929461;0.368919;0.000000;,
    -0.929461;0.368919;0.000000;,
    -0.929461;0.368919;0.000000;,
    -0.001890;-0.999998;0.000000;,
    -0.001890;-0.999998;0.000000;,
    -0.001890;-0.999998;0.000000;,
    -0.001890;-0.999998;0.000000;,
    -0.001890;-0.999998;0.000000;,
    -0.001890;-0.999998;0.000000;,
    0.684416;0.729092;0.000000;,
    0.684416;0.729092;0.000000;,
    0.684416;0.729092;0.000000;,
    0.684416;0.729092;0.000000;,
    0.684416;0.729092;0.000000;,
    0.684416;0.729092;0.000000;,
    -0.001925;0.049044;-0.998795;,
    -0.001925;0.049044;-0.998795;,
    -0.001925;0.049044;-0.998795;,
    -0.001925;0.049044;-0.998795;,
    -0.001925;0.049044;-0.998795;,
    -0.001925;0.049044;-0.998795;,
    0.000927;-0.419533;0.907739;,
    0.000927;-0.419534;0.907739;,
    0.000927;-0.419533;0.907739;,
    0.000927;-0.419533;0.907739;,
    0.000927;-0.419533;0.907739;,
    0.000927;-0.419533;0.907739;,
    -0.999998;0.001960;0.000151;,
    -0.999998;0.001960;0.000151;,
    -0.999998;0.001960;0.000151;,
    -0.001925;0.049044;-0.998795;,
    -0.001925;0.049044;-0.998795;,
    -0.001925;0.049044;-0.998795;,
    -0.001925;0.049044;-0.998795;,
    -0.001925;0.049044;-0.998795;,
    -0.001925;0.049044;-0.998795;,
    0.000927;-0.419534;0.907739;,
    0.000927;-0.419533;0.907739;,
    0.000927;-0.419533;0.907739;,
    0.000927;-0.419533;0.907739;,
    0.000927;-0.419534;0.907739;,
    0.000927;-0.419534;0.907739;,
    0.999998;-0.001960;-0.000152;,
    0.999998;-0.001960;-0.000152;,
    0.999998;-0.001960;-0.000152;,
    0.734129;-0.291388;0.613308;,
    0.734129;-0.291388;0.613308;,
    0.734129;-0.291388;0.613308;,
    -0.929461;0.368919;-0.000000;,
    -0.929461;0.368919;-0.000000;,
    -0.929461;0.368919;-0.000000;,
    -0.929461;0.368919;-0.000000;,
    -0.929461;0.368919;-0.000000;,
    -0.929461;0.368919;-0.000000;,
    -0.001890;-0.999998;-0.000000;,
    -0.001890;-0.999998;-0.000000;,
    -0.001890;-0.999998;-0.000000;,
    -0.001890;-0.999998;-0.000000;,
    -0.001890;-0.999998;-0.000000;,
    -0.001890;-0.999998;-0.000000;,
    0.684416;0.729092;0.000000;,
    0.684416;0.729092;0.000000;,
    0.684416;0.729092;0.000000;,
    0.684416;0.729092;0.000000;,
    0.684416;0.729092;0.000000;,
    0.684416;0.729092;0.000000;,
    0.952213;-0.305191;0.012235;,
    0.952213;-0.305191;0.012235;,
    0.952213;-0.305191;0.012235;,
    -0.113204;0.993572;0.000005;,
    -0.113204;0.993572;0.000005;,
    -0.113204;0.993572;0.000005;,
    -0.113204;0.993572;0.000005;,
    -0.113204;0.993572;0.000005;,
    -0.113204;0.993572;0.000005;,
    -0.859151;-0.511575;0.012301;,
    -0.859151;-0.511575;0.012301;,
    -0.859151;-0.511575;0.012301;,
    0.113111;-0.992751;0.040636;,
    0.113111;-0.992751;0.040636;,
    0.113111;-0.992751;0.040636;;
    36;
    3;0,1,2;,
    3;3,4,5;,
    3;6,7,8;,
    3;9,10,11;,
    3;12,13,14;,
    3;15,16,17;,
    3;18,19,20;,
    3;21,22,23;,
    3;24,25,26;,
    3;27,28,29;,
    3;30,31,32;,
    3;33,34,35;,
    3;36,37,38;,
    3;39,40,41;,
    3;42,43,44;,
    3;45,46,47;,
    3;48,49,50;,
    3;51,52,53;,
    3;54,55,56;,
    3;57,58,59;,
    3;60,61,62;,
    3;63,64,65;,
    3;66,67,68;,
    3;69,70,71;,
    3;72,73,74;,
    3;75,76,77;,
    3;78,79,80;,
    3;81,82,83;,
    3;84,85,86;,
    3;87,88,89;,
    3;90,91,92;,
    3;93,94,95;,
    3;96,97,98;,
    3;99,100,101;,
    3;102,103,104;,
    3;105,106,107;;
   }

   MeshMaterialList  {
    1;
    36;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;
    { skyscrapers }
   }

   MeshTextureCoords  {
    108;
    0.933930;0.356468;,
    0.952214;0.356341;,
    0.943004;0.342294;,
    0.799552;0.620843;,
    0.998908;0.620842;,
    0.998585;0.361078;,
    0.998585;0.361078;,
    0.799050;0.361066;,
    0.799552;0.620843;,
    0.799552;0.620843;,
    0.998908;0.620842;,
    0.998585;0.361078;,
    0.998585;0.361078;,
    0.799050;0.361066;,
    0.799552;0.620843;,
    0.998908;0.620842;,
    0.799552;0.620843;,
    0.799050;0.361066;,
    0.799050;0.361066;,
    0.998585;0.361078;,
    0.998908;0.620842;,
    0.522868;0.243839;,
    0.616802;0.243839;,
    0.569835;0.114036;,
    0.609777;0.000766;,
    0.514680;0.000767;,
    0.514682;0.449291;,
    0.514682;0.449291;,
    0.609778;0.449291;,
    0.609777;0.000766;,
    0.627885;0.105326;,
    0.515618;0.001764;,
    0.515620;0.449776;,
    0.515620;0.449776;,
    0.627886;0.449775;,
    0.627885;0.105326;,
    0.515618;0.001764;,
    0.627885;0.105326;,
    0.627886;0.449775;,
    0.627886;0.449775;,
    0.515620;0.449776;,
    0.515618;0.001764;,
    0.896099;0.357055;,
    0.896098;0.316974;,
    0.999285;0.316973;,
    0.999285;0.316973;,
    0.999287;0.357054;,
    0.896099;0.357055;,
    0.999287;0.357054;,
    0.896099;0.357055;,
    0.896098;0.316974;,
    0.896098;0.316974;,
    0.999286;0.316973;,
    0.999287;0.357054;,
    0.896099;0.357055;,
    0.946900;0.334669;,
    0.999287;0.357054;,
    0.896099;0.357055;,
    0.896098;0.316974;,
    0.999285;0.316973;,
    0.999285;0.316973;,
    0.999287;0.357054;,
    0.896099;0.357055;,
    0.999287;0.357054;,
    0.896099;0.357055;,
    0.896098;0.316974;,
    0.896098;0.316974;,
    0.999286;0.316973;,
    0.999287;0.357054;,
    0.896098;0.316974;,
    0.999286;0.316973;,
    0.946504;0.335820;,
    0.522868;0.243839;,
    0.616802;0.243839;,
    0.569835;0.114036;,
    0.609777;0.000766;,
    0.514680;0.000767;,
    0.514681;0.237240;,
    0.514681;0.237240;,
    0.609778;0.237240;,
    0.609777;0.000766;,
    0.627885;0.105326;,
    0.515618;0.001764;,
    0.515577;0.237967;,
    0.515577;0.237967;,
    0.627844;0.238234;,
    0.627885;0.105326;,
    0.515618;0.001764;,
    0.627885;0.105326;,
    0.627844;0.238234;,
    0.627844;0.238234;,
    0.515577;0.237967;,
    0.515618;0.001764;,
    0.583898;0.284453;,
    0.576209;0.284453;,
    0.580356;0.497067;,
    0.576021;0.284616;,
    0.579887;0.284616;,
    0.584034;0.498576;,
    0.584034;0.498576;,
    0.580168;0.498576;,
    0.576021;0.284616;,
    0.573416;0.284697;,
    0.583960;0.284697;,
    0.581065;0.496516;,
    0.580168;0.498576;,
    0.584034;0.498576;,
    0.576021;0.284616;;
   }
  }
 }
}