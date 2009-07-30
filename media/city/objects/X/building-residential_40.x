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

Frame building-residential_40 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,-0.000000,-1.000000,0.000000,0.000000,1.000000,-0.000000,0.000000,0.000000,-12.670539,12.491668,1.000000;;
 }

 Frame {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.000000,0.000000,1.000000;;
  }

  Mesh  {
   93;
   -5.580609;11.139372;12.765059;,
   -5.615761;-10.835243;12.765057;,
   2.110374;-11.169593;6.769390;,
   2.110374;-11.169593;6.769390;,
   2.110378;11.169598;6.769390;,
   -5.580609;11.139372;12.765059;,
   -12.781425;11.169599;0.000001;,
   -12.781425;11.169600;6.769390;,
   -4.982039;11.169599;6.769390;,
   2.110379;11.169597;0.000001;,
   -12.781425;11.169599;0.000001;,
   -4.982039;11.169599;6.769390;,
   2.110379;11.169597;0.000001;,
   -4.982039;11.169599;6.769390;,
   2.110378;11.169598;6.769390;,
   -12.781429;-11.169591;6.769390;,
   -12.781425;11.169600;6.769390;,
   -12.781425;11.169599;0.000001;,
   -12.781425;11.169599;0.000001;,
   -12.781429;-11.169591;0.000001;,
   -12.781429;-11.169591;6.769390;,
   2.110375;-11.169593;0.000001;,
   2.110374;-11.169593;6.769390;,
   -5.729334;-11.169592;6.769390;,
   -12.781429;-11.169591;0.000001;,
   2.110375;-11.169593;0.000001;,
   -5.729334;-11.169592;6.769390;,
   -12.781429;-11.169591;0.000001;,
   -5.729334;-11.169592;6.769390;,
   -12.781429;-11.169591;6.769390;,
   2.110378;11.169598;6.769390;,
   2.110374;-11.169593;6.769390;,
   2.110375;-11.169593;0.000001;,
   2.110375;-11.169593;0.000001;,
   2.110379;11.169597;0.000001;,
   2.110378;11.169598;6.769390;,
   -12.781425;11.169600;6.769390;,
   -12.781429;-11.169591;6.769390;,
   -5.615761;-10.835243;12.765057;,
   -5.615761;-10.835243;12.765057;,
   -5.580609;11.139372;12.765059;,
   -12.781425;11.169600;6.769390;,
   -12.781429;-11.169591;6.769390;,
   -5.729334;-11.169592;6.769390;,
   -5.615761;-10.835243;12.765057;,
   -5.615761;-10.835243;12.765057;,
   -5.729334;-11.169592;6.769390;,
   2.110374;-11.169593;6.769390;,
   2.110378;11.169598;6.769390;,
   -4.982039;11.169599;6.769390;,
   -5.580609;11.139372;12.765059;,
   -5.580609;11.139372;12.765059;,
   -4.982039;11.169599;6.769390;,
   -12.781425;11.169600;6.769390;,
   -0.817525;3.936317;9.223726;,
   14.585687;3.597361;9.223726;,
   14.594389;9.088523;5.728890;,
   14.594389;9.088523;5.728890;,
   -0.832812;9.088522;5.728890;,
   -0.817525;3.936317;9.223726;,
   14.594387;-1.615948;5.728891;,
   -0.832814;-1.615946;5.728891;,
   -0.832812;-1.615946;0.030093;,
   -0.832812;-1.615946;0.030093;,
   14.594387;-1.615948;-0.000000;,
   14.594387;-1.615948;5.728891;,
   14.594389;9.088526;-0.000000;,
   14.594389;9.088523;5.728890;,
   14.594386;3.645772;5.728891;,
   14.594387;-1.615948;-0.000000;,
   14.594389;9.088526;-0.000000;,
   14.594386;3.645772;5.728891;,
   14.594387;-1.615948;-0.000000;,
   14.594386;3.645772;5.728891;,
   14.594387;-1.615948;5.728891;,
   -0.832812;9.088522;5.728890;,
   14.594389;9.088523;5.728890;,
   14.594389;9.088526;-0.000000;,
   14.594389;9.088526;-0.000000;,
   -0.832810;9.088523;0.030092;,
   -0.832812;9.088522;5.728890;,
   -0.832814;-1.615946;5.728891;,
   14.594387;-1.615948;5.728891;,
   14.585687;3.597361;9.223726;,
   14.585687;3.597361;9.223726;,
   -0.817525;3.936317;9.223726;,
   -0.832814;-1.615946;5.728891;,
   14.594387;-1.615948;5.728891;,
   14.594386;3.645772;5.728891;,
   14.585687;3.597361;9.223726;,
   14.585687;3.597361;9.223726;,
   14.594386;3.645772;5.728891;,
   14.594389;9.088523;5.728890;;
   31;
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
   3;90,91,92;;

   MeshNormals  {
    93;
    0.614357;-0.000257;0.789028;,
    0.613050;-0.000981;0.790043;,
    0.613526;-0.000718;0.789675;,
    0.613526;-0.000718;0.789675;,
    0.614821;-0.000000;0.788666;,
    0.614357;-0.000257;0.789028;,
    0.000000;1.000000;-0.000000;,
    0.000000;0.999999;0.001545;,
    0.000000;0.999997;0.002521;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;0.999997;0.002521;,
    0.000000;1.000000;-0.000000;,
    0.000000;0.999997;0.002521;,
    0.000000;0.999999;0.001495;,
    -1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;-0.000000;,
    -0.000000;-1.000000;-0.000000;,
    -0.000000;-0.999864;0.016491;,
    -0.000000;-0.999612;0.027850;,
    -0.000000;-1.000000;-0.000000;,
    -0.000000;-1.000000;-0.000000;,
    -0.000000;-0.999612;0.027850;,
    -0.000000;-1.000000;-0.000000;,
    -0.000000;-0.999612;0.027850;,
    -0.000000;-0.999853;0.017127;,
    1.000000;-0.000000;0.000000;,
    1.000000;-0.000000;0.000000;,
    1.000000;-0.000000;0.000000;,
    1.000000;-0.000000;0.000000;,
    1.000000;-0.000000;0.000000;,
    1.000000;-0.000000;0.000000;,
    -0.640340;0.000761;0.768091;,
    -0.641717;0.000000;0.766942;,
    -0.641253;0.000256;0.767329;,
    -0.641253;0.000256;0.767329;,
    -0.639866;0.001024;0.768486;,
    -0.640340;0.000761;0.768091;,
    -0.000000;-0.999853;0.017127;,
    -0.000000;-0.999612;0.027850;,
    -0.000000;-0.998449;0.055679;,
    -0.000000;-0.998449;0.055679;,
    -0.000000;-0.999612;0.027850;,
    -0.000000;-0.999864;0.016491;,
    0.000000;0.999999;0.001495;,
    0.000000;0.999997;0.002521;,
    0.000000;0.999987;0.005041;,
    0.000000;0.999987;0.005041;,
    0.000000;0.999997;0.002521;,
    0.000000;0.999999;0.001545;,
    0.002986;0.555222;0.831697;,
    0.011814;0.536875;0.843579;,
    0.008925;0.542913;0.839741;,
    0.008925;0.542913;0.839741;,
    -0.000000;0.561358;0.827573;,
    0.002986;0.555222;0.831697;,
    -0.000000;-1.000000;-0.000000;,
    -0.000000;-1.000000;-0.000000;,
    -0.000000;-1.000000;-0.000000;,
    -0.000000;-1.000000;-0.000000;,
    -0.000000;-1.000000;0.000000;,
    -0.000000;-1.000000;-0.000000;,
    1.000000;-0.000000;0.000000;,
    1.000000;-0.000001;0.000660;,
    0.999999;-0.000000;0.001245;,
    1.000000;-0.000000;0.000000;,
    1.000000;-0.000000;0.000000;,
    0.999999;-0.000000;0.001245;,
    1.000000;-0.000000;0.000000;,
    0.999999;-0.000000;0.001245;,
    1.000000;0.000000;0.000680;,
    -0.000000;1.000000;0.000000;,
    -0.000000;1.000000;0.000000;,
    -0.000000;1.000000;0.000000;,
    -0.000000;1.000000;0.000000;,
    -0.000000;1.000000;0.000000;,
    -0.000000;1.000000;0.000000;,
    -0.008833;-0.538650;0.842484;,
    -0.000000;-0.556827;0.830629;,
    -0.002985;-0.550719;0.834686;,
    -0.002985;-0.550719;0.834686;,
    -0.011721;-0.532641;0.846260;,
    -0.008833;-0.538650;0.842484;,
    1.000000;0.000000;0.000680;,
    0.999999;-0.000000;0.001245;,
    0.999997;-0.000000;0.002489;,
    0.999997;-0.000000;0.002489;,
    0.999999;-0.000000;0.001245;,
    1.000000;-0.000001;0.000660;;
    31;
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
    3;90,91,92;;
   }

   MeshMaterialList  {
    1;
    31;
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
    { buildz6 }
   }

   MeshTextureCoords  {
    93;
    0.601810;0.271329;,
    0.602392;0.547062;,
    0.725195;0.546991;,
    0.725195;0.546991;,
    0.725193;0.271273;,
    0.601810;0.271329;,
    0.599203;0.449503;,
    0.599203;0.270702;,
    0.408968;0.270702;,
    0.235206;0.450295;,
    0.599203;0.449503;,
    0.408968;0.270702;,
    0.235206;0.450295;,
    0.408968;0.270702;,
    0.235206;0.271494;,
    0.600686;0.270702;,
    0.003978;0.270702;,
    0.003978;0.449503;,
    0.003978;0.449503;,
    0.600686;0.449503;,
    0.600686;0.270702;,
    0.599203;0.449503;,
    0.599203;0.270702;,
    0.408375;0.270702;,
    0.235206;0.450295;,
    0.599203;0.449503;,
    0.408375;0.270702;,
    0.235206;0.450295;,
    0.408375;0.270702;,
    0.235206;0.271494;,
    0.600686;0.270702;,
    0.003978;0.270702;,
    0.003978;0.449503;,
    0.003978;0.449503;,
    0.600686;0.449503;,
    0.600686;0.270702;,
    0.723844;0.271273;,
    0.723847;0.546991;,
    0.602392;0.547062;,
    0.602392;0.547062;,
    0.601810;0.271329;,
    0.723844;0.271273;,
    0.673530;0.553675;,
    0.673922;0.642272;,
    0.722667;0.643897;,
    0.722667;0.643897;,
    0.673922;0.642272;,
    0.672357;0.745021;,
    0.673530;0.553675;,
    0.673922;0.642272;,
    0.722667;0.643897;,
    0.722667;0.643897;,
    0.673922;0.642272;,
    0.672357;0.745021;,
    0.598119;0.359922;,
    0.600547;0.539680;,
    0.725195;0.539608;,
    0.725195;0.539608;,
    0.725193;0.359866;,
    0.598119;0.359922;,
    0.284707;0.429432;,
    0.587949;0.429432;,
    0.587949;0.549171;,
    0.587949;0.549171;,
    0.284707;0.549171;,
    0.284707;0.429432;,
    0.558714;0.548919;,
    0.558714;0.429432;,
    0.464254;0.429432;,
    0.373241;0.549710;,
    0.558714;0.548919;,
    0.464254;0.429432;,
    0.373241;0.549710;,
    0.464254;0.429432;,
    0.373241;0.430223;,
    0.587949;0.429432;,
    0.284707;0.429432;,
    0.284707;0.549171;,
    0.284707;0.549171;,
    0.587949;0.549171;,
    0.587949;0.429432;,
    0.723844;0.359866;,
    0.723847;0.539608;,
    0.600547;0.539680;,
    0.600547;0.539680;,
    0.598119;0.359922;,
    0.723844;0.359866;,
    0.400658;0.280196;,
    0.289919;0.361015;,
    0.267550;0.280893;,
    0.267550;0.280893;,
    0.289919;0.361015;,
    0.401897;0.281369;;
   }
  }
 }
}