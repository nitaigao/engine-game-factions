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

Frame building-scyscrapers_05 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,-0.000000,-1.000000,0.000000,0.000000,1.000000,-0.000000,0.000000,0.000000,-12.670539,12.491668,1.000000;;
 }

 Frame {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.000000,0.000000,1.000000;;
  }

  Mesh  {
   327;
   15.750013;-4.877812;67.324547;,
   15.750014;10.438917;67.324547;,
   -15.620964;10.438910;67.324547;,
   -15.620964;10.438910;67.324547;,
   -15.620965;-4.877819;67.324547;,
   15.750013;-4.877812;67.324547;,
   -15.620965;-4.877819;67.324547;,
   -15.620964;10.438910;67.324547;,
   -15.620964;10.438910;19.369558;,
   -15.620964;10.438910;19.369558;,
   -15.620964;-4.877818;19.369558;,
   -15.620965;-4.877819;67.324547;,
   15.750013;-4.877812;67.324547;,
   -15.620965;-4.877819;67.324547;,
   -15.620964;-4.877818;19.369558;,
   -15.620964;-4.877818;19.369558;,
   15.750013;-4.877812;19.369558;,
   15.750013;-4.877812;67.324547;,
   15.750014;10.438917;67.324547;,
   15.750013;-4.877812;67.324547;,
   15.750013;-4.877812;19.369558;,
   15.750013;-4.877812;19.369558;,
   15.750013;10.438917;19.369558;,
   15.750014;10.438917;67.324547;,
   -15.620964;10.438910;67.324547;,
   15.750014;10.438917;67.324547;,
   15.750013;10.438917;19.369558;,
   15.750013;10.438917;19.369558;,
   -15.620964;10.438910;19.369558;,
   -15.620964;10.438910;67.324547;,
   -15.620964;10.438910;19.369558;,
   15.750013;10.438917;19.369558;,
   19.489712;14.329534;14.762194;,
   19.489712;14.329534;14.762194;,
   -19.181004;14.329523;14.762194;,
   -15.620964;10.438910;19.369558;,
   15.750013;10.438917;19.369558;,
   15.750013;-4.877812;19.369558;,
   19.489716;-8.059641;14.762194;,
   19.489716;-8.059641;14.762194;,
   19.489712;14.329534;14.762194;,
   15.750013;10.438917;19.369558;,
   15.750013;-4.877812;19.369558;,
   -15.620964;-4.877818;19.369558;,
   -19.181002;-8.059649;14.762194;,
   -19.181002;-8.059649;14.762194;,
   19.489716;-8.059641;14.762194;,
   15.750013;-4.877812;19.369558;,
   -15.620964;-4.877818;19.369558;,
   -15.620964;10.438910;19.369558;,
   -19.181004;14.329523;14.762194;,
   -19.181004;14.329523;14.762194;,
   -19.181002;-8.059649;14.762194;,
   -15.620964;-4.877818;19.369558;,
   -19.181004;14.329523;14.762194;,
   19.489712;14.329534;14.762194;,
   19.489712;14.329534;-0.000001;,
   19.489712;14.329534;-0.000001;,
   -19.181004;14.329523;-0.000001;,
   -19.181004;14.329523;14.762194;,
   19.489712;14.329534;14.762194;,
   19.489716;-8.059641;14.762194;,
   19.489716;-8.059641;-0.000001;,
   19.489716;-8.059641;-0.000001;,
   19.489712;14.329534;-0.000001;,
   19.489712;14.329534;14.762194;,
   19.489716;-8.059641;14.762194;,
   -19.181002;-8.059649;14.762194;,
   -19.181002;-8.059649;-0.000001;,
   -19.181002;-8.059649;-0.000001;,
   19.489716;-8.059641;-0.000001;,
   19.489716;-8.059641;14.762194;,
   -19.181002;-8.059649;14.762194;,
   -19.181004;14.329523;14.762194;,
   -19.181004;14.329523;-0.000001;,
   -19.181004;14.329523;-0.000001;,
   -19.181002;-8.059649;-0.000001;,
   -19.181002;-8.059649;14.762194;,
   0.310518;-14.329520;0.025412;,
   5.138714;-12.434641;0.025412;,
   5.138714;-12.434641;6.297643;,
   5.138714;-12.434641;6.297643;,
   0.310518;-14.329520;6.297643;,
   0.310518;-14.329520;0.025412;,
   5.138714;-12.434641;0.025412;,
   7.138617;-7.859998;0.025412;,
   7.138617;-7.859998;6.297643;,
   7.138617;-7.859998;6.297643;,
   5.138714;-12.434641;6.297643;,
   5.138714;-12.434641;0.025412;,
   -6.517582;-7.860002;0.025412;,
   -4.517677;-12.434645;0.025412;,
   -4.517677;-12.434645;6.297643;,
   -4.517677;-12.434645;6.297643;,
   -6.517582;-7.860002;6.297643;,
   -6.517582;-7.860002;0.025412;,
   -4.517677;-12.434645;0.025412;,
   0.310518;-14.329520;0.025412;,
   0.310518;-14.329520;6.297643;,
   0.310518;-14.329520;6.297643;,
   -4.517677;-12.434645;6.297643;,
   -4.517677;-12.434645;0.025412;,
   0.310518;-14.329520;6.297643;,
   5.138714;-12.434641;6.297643;,
   7.138617;-7.859998;6.297643;,
   -4.517677;-12.434645;6.297643;,
   0.310518;-14.329520;6.297643;,
   7.138617;-7.859998;6.297643;,
   -6.517582;-7.860002;6.297643;,
   -4.517677;-12.434645;6.297643;,
   7.138617;-7.859998;6.297643;,
   0.310518;-13.174802;6.170892;,
   4.068650;-11.618130;6.170892;,
   4.068650;-11.618130;14.662165;,
   4.068650;-11.618130;14.662165;,
   0.310518;-13.174802;14.662165;,
   0.310518;-13.174802;6.170892;,
   4.068650;-11.618130;6.170892;,
   5.625319;-7.859998;6.170892;,
   5.625319;-7.859998;14.662165;,
   5.625319;-7.859998;14.662165;,
   4.068650;-11.618130;14.662165;,
   4.068650;-11.618130;6.170892;,
   -5.004284;-7.860001;6.170892;,
   -3.447614;-11.618133;6.170892;,
   -3.447614;-11.618133;14.662165;,
   -3.447614;-11.618133;14.662165;,
   -5.004284;-7.860001;14.662165;,
   -5.004284;-7.860001;6.170892;,
   -3.447614;-11.618133;6.170892;,
   0.310518;-13.174802;6.170892;,
   0.310518;-13.174802;14.662165;,
   0.310518;-13.174802;14.662165;,
   -3.447614;-11.618133;14.662165;,
   -3.447614;-11.618133;6.170892;,
   0.310518;-13.174802;14.662165;,
   4.068650;-11.618130;14.662165;,
   5.625319;-7.859998;14.662165;,
   -3.447614;-11.618133;14.662165;,
   0.310518;-13.174802;14.662165;,
   5.625319;-7.859998;14.662165;,
   -5.004284;-7.860001;14.662165;,
   -3.447614;-11.618133;14.662165;,
   5.625319;-7.859998;14.662165;,
   -19.489712;3.996974;108.166771;,
   -19.489702;-8.318777;108.166771;,
   -3.404210;3.996971;108.166771;,
   -3.404201;-8.318777;108.166771;,
   -3.404210;3.996971;108.166771;,
   -19.489702;-8.318777;108.166771;,
   -3.404210;3.996971;108.166771;,
   -3.404201;-8.318777;108.166771;,
   -3.404210;3.996971;60.211777;,
   -3.404203;-8.318777;60.211777;,
   -3.404210;3.996971;60.211777;,
   -3.404201;-8.318777;108.166771;,
   -3.404201;-8.318777;108.166771;,
   -19.489702;-8.318777;108.166771;,
   -3.404203;-8.318777;60.211777;,
   -19.489702;-8.318776;60.211777;,
   -3.404203;-8.318777;60.211777;,
   -19.489702;-8.318777;108.166771;,
   -19.489702;-8.318777;108.166771;,
   -19.489712;3.996974;108.166771;,
   -19.489702;-8.318776;60.211777;,
   -19.489712;3.996974;60.211777;,
   -19.489702;-8.318776;60.211777;,
   -19.489712;3.996974;108.166771;,
   -19.489712;3.996974;108.166771;,
   -3.404210;3.996971;108.166771;,
   -19.489712;3.996974;60.211777;,
   -3.404210;3.996971;60.211777;,
   -19.489712;3.996974;60.211777;,
   -3.404210;3.996971;108.166771;,
   8.357347;-3.623595;122.238770;,
   8.357349;9.163367;122.238770;,
   -7.728153;9.163359;122.238770;,
   -7.728153;9.163359;122.238770;,
   -7.728155;-3.623599;122.238770;,
   8.357347;-3.623595;122.238770;,
   -7.728155;-3.623599;122.238770;,
   -7.728153;9.163359;122.238770;,
   -7.728152;9.163359;66.988579;,
   -7.728152;9.163359;66.988579;,
   -7.728152;-3.623599;66.988579;,
   -7.728155;-3.623599;122.238770;,
   8.357347;-3.623595;122.238770;,
   -7.728155;-3.623599;122.238770;,
   -7.728152;-3.623599;66.988579;,
   -7.728152;-3.623599;66.988579;,
   8.357347;-3.623594;66.988579;,
   8.357347;-3.623595;122.238770;,
   8.357349;9.163367;122.238770;,
   8.357347;-3.623595;122.238770;,
   8.357347;-3.623594;66.988579;,
   8.357347;-3.623594;66.988579;,
   8.357349;9.163366;66.988579;,
   8.357349;9.163367;122.238770;,
   -7.728153;9.163359;122.238770;,
   8.357349;9.163367;122.238770;,
   8.357349;9.163366;66.988579;,
   8.357349;9.163366;66.988579;,
   -7.728152;9.163359;66.988579;,
   -7.728153;9.163359;122.238770;,
   -3.404202;-4.668917;57.067444;,
   -3.404209;3.996971;57.067444;,
   -3.404210;3.996971;60.211777;,
   -3.404210;3.996971;60.211777;,
   -3.404203;-8.318777;60.211777;,
   -3.404202;-4.668917;57.067444;,
   -15.658937;-4.668916;57.067444;,
   -3.404202;-4.668917;57.067444;,
   -3.404203;-8.318777;60.211777;,
   -3.404203;-8.318777;60.211777;,
   -19.489702;-8.318776;60.211777;,
   -15.658937;-4.668916;57.067444;,
   -15.658944;3.996975;57.067444;,
   -15.658937;-4.668916;57.067444;,
   -19.489702;-8.318776;60.211777;,
   -19.489702;-8.318776;60.211777;,
   -19.489712;3.996974;60.211777;,
   -15.658944;3.996975;57.067444;,
   -3.404209;3.996971;57.067444;,
   -15.658944;3.996975;57.067444;,
   -19.489712;3.996974;60.211777;,
   -19.489712;3.996974;60.211777;,
   -3.404210;3.996971;60.211777;,
   -3.404209;3.996971;57.067444;,
   19.249523;1.469036;89.052368;,
   19.249517;13.784790;89.052368;,
   3.164024;1.469039;89.052368;,
   3.164009;13.784792;89.052368;,
   3.164024;1.469039;89.052368;,
   19.249517;13.784790;89.052368;,
   3.164024;1.469039;89.052368;,
   3.164009;13.784792;89.052368;,
   3.164024;1.469040;41.097366;,
   3.164018;13.784792;41.097366;,
   3.164024;1.469040;41.097366;,
   3.164009;13.784792;89.052368;,
   3.164009;13.784792;89.052368;,
   19.249517;13.784790;89.052368;,
   3.164018;13.784792;41.097366;,
   19.249517;13.784789;41.097366;,
   3.164018;13.784792;41.097366;,
   19.249517;13.784790;89.052368;,
   19.249517;13.784790;89.052368;,
   19.249523;1.469036;89.052368;,
   19.249517;13.784789;41.097366;,
   19.249523;1.469036;41.097366;,
   19.249517;13.784789;41.097366;,
   19.249523;1.469036;89.052368;,
   19.249523;1.469036;89.052368;,
   3.164024;1.469039;89.052368;,
   19.249523;1.469036;41.097366;,
   3.164024;1.469040;41.097366;,
   19.249523;1.469036;41.097366;,
   3.164024;1.469039;89.052368;,
   3.164016;10.134931;37.953033;,
   3.164020;1.469040;37.953033;,
   3.164024;1.469040;41.097366;,
   3.164024;1.469040;41.097366;,
   3.164018;13.784792;41.097366;,
   3.164016;10.134931;37.953033;,
   15.418753;10.134929;37.953033;,
   3.164016;10.134931;37.953033;,
   3.164018;13.784792;41.097366;,
   3.164018;13.784792;41.097366;,
   19.249517;13.784789;41.097366;,
   15.418753;10.134929;37.953033;,
   15.418761;1.469036;37.953033;,
   15.418753;10.134929;37.953033;,
   19.249517;13.784789;41.097366;,
   19.249517;13.784789;41.097366;,
   19.249523;1.469036;41.097366;,
   15.418761;1.469036;37.953033;,
   3.164020;1.469040;37.953033;,
   15.418761;1.469036;37.953033;,
   19.249523;1.469036;41.097366;,
   19.249523;1.469036;41.097366;,
   3.164024;1.469040;41.097366;,
   3.164020;1.469040;37.953033;,
   5.711648;-1.864673;121.941376;,
   6.135312;-0.925091;121.941376;,
   5.825210;-0.925202;145.041183;,
   6.135312;-0.925091;121.941376;,
   5.287977;-0.925092;121.941376;,
   5.599760;-0.925202;145.041183;,
   5.599760;-0.925202;145.041183;,
   5.825210;-0.925202;145.041183;,
   6.135312;-0.925091;121.941376;,
   5.287977;-0.925092;121.941376;,
   5.711648;-1.864673;121.941376;,
   5.599760;-0.925202;145.041183;,
   5.825210;-0.925202;145.041183;,
   5.599760;-0.925202;145.041183;,
   5.711648;-1.864673;121.941376;,
   3.400579;-1.864673;121.941383;,
   3.824245;-0.925092;121.941383;,
   3.514143;-0.925202;134.772491;,
   3.824245;-0.925092;121.941383;,
   2.976910;-0.925092;121.941383;,
   3.288693;-0.925203;134.772491;,
   3.288693;-0.925203;134.772491;,
   3.514143;-0.925202;134.772491;,
   3.824245;-0.925092;121.941383;,
   2.976910;-0.925092;121.941383;,
   3.400579;-1.864673;121.941383;,
   3.288693;-0.925203;134.772491;,
   3.514143;-0.925202;134.772491;,
   3.288693;-0.925203;134.772491;,
   3.400579;-1.864673;121.941383;,
   -16.905357;-7.006186;107.864868;,
   -17.008242;-5.980651;107.864868;,
   -17.276745;-6.135800;120.695976;,
   -17.008242;-5.980651;107.864868;,
   -17.742056;-6.404318;107.864868;,
   -17.471987;-6.248524;120.695976;,
   -17.471987;-6.248524;120.695976;,
   -17.276745;-6.135800;120.695976;,
   -17.008242;-5.980651;107.864868;,
   -17.742056;-6.404318;107.864868;,
   -16.905357;-7.006186;107.864868;,
   -17.471987;-6.248524;120.695976;,
   -17.276745;-6.135800;120.695976;,
   -17.471987;-6.248524;120.695976;,
   -16.905357;-7.006186;107.864868;;
   109;
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
   3;105,106,107;,
   3;108,109,110;,
   3;111,112,113;,
   3;114,115,116;,
   3;117,118,119;,
   3;120,121,122;,
   3;123,124,125;,
   3;126,127,128;,
   3;129,130,131;,
   3;132,133,134;,
   3;135,136,137;,
   3;138,139,140;,
   3;141,142,143;,
   3;144,145,146;,
   3;147,148,149;,
   3;150,151,152;,
   3;153,154,155;,
   3;156,157,158;,
   3;159,160,161;,
   3;162,163,164;,
   3;165,166,167;,
   3;168,169,170;,
   3;171,172,173;,
   3;174,175,176;,
   3;177,178,179;,
   3;180,181,182;,
   3;183,184,185;,
   3;186,187,188;,
   3;189,190,191;,
   3;192,193,194;,
   3;195,196,197;,
   3;198,199,200;,
   3;201,202,203;,
   3;204,205,206;,
   3;207,208,209;,
   3;210,211,212;,
   3;213,214,215;,
   3;216,217,218;,
   3;219,220,221;,
   3;222,223,224;,
   3;225,226,227;,
   3;228,229,230;,
   3;231,232,233;,
   3;234,235,236;,
   3;237,238,239;,
   3;240,241,242;,
   3;243,244,245;,
   3;246,247,248;,
   3;249,250,251;,
   3;252,253,254;,
   3;255,256,257;,
   3;258,259,260;,
   3;261,262,263;,
   3;264,265,266;,
   3;267,268,269;,
   3;270,271,272;,
   3;273,274,275;,
   3;276,277,278;,
   3;279,280,281;,
   3;282,283,284;,
   3;285,286,287;,
   3;288,289,290;,
   3;291,292,293;,
   3;294,295,296;,
   3;297,298,299;,
   3;300,301,302;,
   3;303,304,305;,
   3;306,307,308;,
   3;309,310,311;,
   3;312,313,314;,
   3;315,316,317;,
   3;318,319,320;,
   3;321,322,323;,
   3;324,325,326;;

   MeshNormals  {
    327;
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    -1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    0.000000;-1.000000;-0.000000;,
    0.000000;-1.000000;-0.000000;,
    0.000000;-1.000000;-0.000000;,
    0.000000;-1.000000;-0.000000;,
    0.000000;-1.000000;-0.000000;,
    0.000000;-1.000000;-0.000000;,
    1.000000;-0.000000;-0.000000;,
    1.000000;-0.000000;-0.000000;,
    1.000000;-0.000000;-0.000000;,
    1.000000;-0.000000;-0.000000;,
    1.000000;0.000000;-0.000000;,
    1.000000;-0.000000;-0.000000;,
    -0.000000;1.000000;0.000000;,
    -0.000000;1.000000;0.000000;,
    -0.000000;1.000000;0.000000;,
    -0.000000;1.000000;0.000000;,
    -0.000000;1.000000;0.000000;,
    -0.000000;1.000000;0.000000;,
    -0.000000;0.764034;0.645176;,
    -0.000000;0.764034;0.645176;,
    -0.000000;0.764034;0.645176;,
    -0.000000;0.764034;0.645176;,
    -0.000000;0.764034;0.645176;,
    -0.000000;0.764034;0.645176;,
    0.776426;0.000000;0.630208;,
    0.776426;0.000000;0.630209;,
    0.776426;0.000000;0.630209;,
    0.776426;0.000000;0.630209;,
    0.776426;0.000000;0.630208;,
    0.776426;0.000000;0.630208;,
    0.000000;-0.822851;0.568258;,
    0.000000;-0.822851;0.568258;,
    0.000000;-0.822851;0.568258;,
    0.000000;-0.822851;0.568258;,
    0.000000;-0.822851;0.568258;,
    0.000000;-0.822851;0.568258;,
    -0.791301;-0.000000;0.611426;,
    -0.791301;0.000000;0.611426;,
    -0.791301;-0.000000;0.611426;,
    -0.791301;-0.000000;0.611426;,
    -0.791301;-0.000000;0.611426;,
    -0.791301;-0.000000;0.611426;,
    -0.000000;1.000000;0.000000;,
    -0.000000;1.000000;0.000000;,
    -0.000000;1.000000;0.000000;,
    -0.000000;1.000000;0.000000;,
    -0.000000;1.000000;0.000000;,
    -0.000000;1.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -1.000000;-0.000000;0.000000;,
    -1.000000;-0.000000;0.000000;,
    -1.000000;-0.000000;0.000000;,
    -1.000000;-0.000000;0.000000;,
    -1.000000;-0.000000;0.000000;,
    -1.000000;-0.000000;0.000000;,
    0.365333;-0.930877;0.000000;,
    0.365333;-0.930877;0.000000;,
    0.365333;-0.930877;0.000000;,
    0.365333;-0.930877;0.000000;,
    0.365333;-0.930877;0.000000;,
    0.365333;-0.930877;0.000000;,
    0.916268;-0.400566;0.000000;,
    0.916268;-0.400566;0.000000;,
    0.916268;-0.400566;0.000000;,
    0.916268;-0.400566;0.000000;,
    0.916268;-0.400566;0.000000;,
    0.916268;-0.400566;0.000000;,
    -0.916268;-0.400566;0.000000;,
    -0.916268;-0.400566;0.000000;,
    -0.916268;-0.400566;0.000000;,
    -0.916268;-0.400566;0.000000;,
    -0.916268;-0.400566;0.000000;,
    -0.916268;-0.400566;0.000000;,
    -0.365332;-0.930877;0.000000;,
    -0.365332;-0.930877;0.000000;,
    -0.365332;-0.930877;0.000000;,
    -0.365332;-0.930877;0.000000;,
    -0.365332;-0.930877;0.000000;,
    -0.365332;-0.930877;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.382684;-0.923879;0.000000;,
    0.382684;-0.923879;0.000000;,
    0.382684;-0.923879;0.000000;,
    0.382684;-0.923879;0.000000;,
    0.382684;-0.923879;0.000000;,
    0.382684;-0.923879;0.000000;,
    0.923880;-0.382683;0.000000;,
    0.923880;-0.382683;0.000000;,
    0.923880;-0.382683;0.000000;,
    0.923880;-0.382683;0.000000;,
    0.923880;-0.382683;0.000000;,
    0.923880;-0.382683;0.000000;,
    -0.923879;-0.382684;0.000000;,
    -0.923879;-0.382684;0.000000;,
    -0.923879;-0.382684;0.000000;,
    -0.923879;-0.382684;0.000000;,
    -0.923879;-0.382684;0.000000;,
    -0.923879;-0.382684;0.000000;,
    -0.382683;-0.923880;0.000000;,
    -0.382683;-0.923880;0.000000;,
    -0.382683;-0.923880;0.000000;,
    -0.382683;-0.923880;0.000000;,
    -0.382683;-0.923880;0.000000;,
    -0.382683;-0.923880;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    1.000000;0.000001;0.000000;,
    1.000000;0.000001;-0.000000;,
    1.000000;0.000001;0.000000;,
    1.000000;0.000001;0.000000;,
    1.000000;0.000001;0.000000;,
    1.000000;0.000001;-0.000000;,
    0.000000;-1.000000;0.000000;,
    -0.000000;-1.000000;-0.000000;,
    -0.000000;-1.000000;-0.000000;,
    -0.000000;-1.000000;-0.000000;,
    -0.000000;-1.000000;-0.000000;,
    -0.000000;-1.000000;-0.000000;,
    -1.000000;-0.000001;-0.000000;,
    -1.000000;-0.000001;-0.000000;,
    -1.000000;-0.000001;-0.000000;,
    -1.000000;-0.000001;0.000000;,
    -1.000000;-0.000001;-0.000000;,
    -1.000000;-0.000001;-0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    -1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    0.000000;-1.000000;-0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;-0.000000;,
    0.000000;-1.000000;-0.000000;,
    0.000000;-1.000000;-0.000000;,
    0.000000;-1.000000;-0.000000;,
    1.000000;-0.000000;-0.000000;,
    1.000000;-0.000000;-0.000000;,
    1.000000;-0.000000;0.000000;,
    1.000000;-0.000000;0.000000;,
    1.000000;-0.000000;0.000000;,
    1.000000;-0.000000;-0.000000;,
    -0.000001;1.000000;-0.000000;,
    -0.000001;1.000000;-0.000000;,
    -0.000000;1.000000;-0.000000;,
    -0.000000;1.000000;-0.000000;,
    -0.000000;1.000000;-0.000000;,
    -0.000001;1.000000;-0.000000;,
    1.000000;0.000001;0.000001;,
    1.000000;0.000001;0.000000;,
    1.000000;0.000001;0.000000;,
    1.000000;0.000001;0.000000;,
    1.000000;0.000001;0.000000;,
    1.000000;0.000001;0.000001;,
    -0.000000;-0.652690;-0.757625;,
    -0.000000;-0.652690;-0.757625;,
    -0.000000;-0.652690;-0.757625;,
    -0.000000;-0.652690;-0.757625;,
    -0.000000;-0.652690;-0.757625;,
    -0.000000;-0.652690;-0.757625;,
    -0.634454;-0.000001;-0.772961;,
    -0.634454;-0.000001;-0.772961;,
    -0.634454;-0.000001;-0.772961;,
    -0.634454;-0.000001;-0.772961;,
    -0.634454;-0.000000;-0.772961;,
    -0.634454;-0.000001;-0.772961;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    -1.000000;-0.000001;-0.000000;,
    -1.000000;-0.000001;-0.000000;,
    -1.000000;-0.000001;0.000001;,
    -1.000000;-0.000000;0.000000;,
    -1.000000;-0.000001;0.000001;,
    -1.000000;-0.000001;-0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    1.000000;0.000000;-0.000000;,
    1.000000;0.000000;-0.000000;,
    1.000000;0.000000;-0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;-0.000000;,
    1.000000;0.000000;-0.000000;,
    -0.000000;-1.000000;0.000000;,
    -0.000000;-1.000000;-0.000000;,
    -0.000000;-1.000000;0.000000;,
    -0.000000;-1.000000;-0.000000;,
    -0.000000;-1.000000;0.000000;,
    -0.000000;-1.000000;-0.000000;,
    -1.000000;-0.000000;0.000001;,
    -1.000000;-0.000000;0.000001;,
    -1.000000;-0.000001;0.000001;,
    -1.000000;-0.000001;0.000001;,
    -1.000000;-0.000000;0.000000;,
    -1.000000;-0.000000;0.000001;,
    0.000000;0.652690;-0.757625;,
    0.000000;0.652690;-0.757625;,
    0.000000;0.652690;-0.757625;,
    0.000000;0.652690;-0.757625;,
    0.000000;0.652690;-0.757625;,
    0.000000;0.652690;-0.757625;,
    0.634454;0.000000;-0.772960;,
    0.634454;0.000001;-0.772961;,
    0.634454;0.000000;-0.772961;,
    0.634454;0.000000;-0.772961;,
    0.634455;0.000000;-0.772960;,
    0.634454;0.000000;-0.772960;,
    -0.000000;-1.000000;0.000000;,
    -0.000000;-1.000000;0.000001;,
    -0.000000;-1.000000;0.000000;,
    -0.000000;-1.000000;0.000000;,
    -0.000000;-1.000000;-0.000000;,
    -0.000000;-1.000000;0.000000;,
    0.911543;-0.411022;0.012235;,
    0.911543;-0.411022;0.012235;,
    0.911543;-0.411022;0.012235;,
    -0.000000;1.000000;0.000005;,
    -0.000000;1.000000;0.000005;,
    -0.000000;1.000000;0.000005;,
    -0.000000;1.000000;0.000005;,
    0.000000;1.000000;0.000005;,
    -0.000000;1.000000;0.000005;,
    -0.911540;-0.411026;0.012301;,
    -0.911540;-0.411026;0.012301;,
    -0.911540;-0.411026;0.012301;,
    0.000000;-0.999174;0.040636;,
    0.000000;-0.999174;0.040636;,
    0.000000;-0.999174;0.040636;,
    0.911390;-0.410955;0.022023;,
    0.911390;-0.410955;0.022023;,
    0.911390;-0.410955;0.022023;,
    0.000000;1.000000;0.000009;,
    0.000000;1.000000;0.000009;,
    -0.000000;1.000000;0.000009;,
    -0.000000;1.000000;0.000009;,
    -0.000000;1.000000;0.000009;,
    0.000000;1.000000;0.000009;,
    -0.911387;-0.410955;0.022142;,
    -0.911387;-0.410955;0.022142;,
    -0.911387;-0.410955;0.022142;,
    0.000000;-0.997330;0.073023;,
    0.000000;-0.997330;0.073023;,
    0.000000;-0.997330;0.073023;,
    0.994764;0.099797;0.022023;,
    0.994764;0.099797;0.022023;,
    0.994764;0.099797;0.022023;,
    -0.500000;0.866026;0.000009;,
    -0.500000;0.866026;0.000009;,
    -0.500004;0.866023;0.000009;,
    -0.500004;0.866023;0.000009;,
    -0.500004;0.866023;0.000009;,
    -0.500000;0.866026;0.000009;,
    -0.583807;-0.811590;0.022142;,
    -0.583807;-0.811590;0.022142;,
    -0.583807;-0.811590;0.022142;,
    0.498670;-0.863711;0.073023;,
    0.498670;-0.863711;0.073023;,
    0.498670;-0.863711;0.073023;;
    109;
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
    3;105,106,107;,
    3;108,109,110;,
    3;111,112,113;,
    3;114,115,116;,
    3;117,118,119;,
    3;120,121,122;,
    3;123,124,125;,
    3;126,127,128;,
    3;129,130,131;,
    3;132,133,134;,
    3;135,136,137;,
    3;138,139,140;,
    3;141,142,143;,
    3;144,145,146;,
    3;147,148,149;,
    3;150,151,152;,
    3;153,154,155;,
    3;156,157,158;,
    3;159,160,161;,
    3;162,163,164;,
    3;165,166,167;,
    3;168,169,170;,
    3;171,172,173;,
    3;174,175,176;,
    3;177,178,179;,
    3;180,181,182;,
    3;183,184,185;,
    3;186,187,188;,
    3;189,190,191;,
    3;192,193,194;,
    3;195,196,197;,
    3;198,199,200;,
    3;201,202,203;,
    3;204,205,206;,
    3;207,208,209;,
    3;210,211,212;,
    3;213,214,215;,
    3;216,217,218;,
    3;219,220,221;,
    3;222,223,224;,
    3;225,226,227;,
    3;228,229,230;,
    3;231,232,233;,
    3;234,235,236;,
    3;237,238,239;,
    3;240,241,242;,
    3;243,244,245;,
    3;246,247,248;,
    3;249,250,251;,
    3;252,253,254;,
    3;255,256,257;,
    3;258,259,260;,
    3;261,262,263;,
    3;264,265,266;,
    3;267,268,269;,
    3;270,271,272;,
    3;273,274,275;,
    3;276,277,278;,
    3;279,280,281;,
    3;282,283,284;,
    3;285,286,287;,
    3;288,289,290;,
    3;291,292,293;,
    3;294,295,296;,
    3;297,298,299;,
    3;300,301,302;,
    3;303,304,305;,
    3;306,307,308;,
    3;309,310,311;,
    3;312,313,314;,
    3;315,316,317;,
    3;318,319,320;,
    3;321,322,323;,
    3;324,325,326;;
   }

   MeshMaterialList  {
    1;
    109;
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
    0,
    0,
    0,
    0;
    { skyscrapers }
   }

   MeshTextureCoords  {
    327;
    0.999565;0.062518;,
    0.891206;0.062518;,
    0.891206;0.134392;,
    0.891206;0.134392;,
    0.999565;0.134392;,
    0.999565;0.062518;,
    0.214090;0.000000;,
    0.306225;0.000000;,
    0.306225;0.199227;,
    0.306225;0.199227;,
    0.214090;0.199227;,
    0.214090;0.000000;,
    0.300687;0.000000;,
    0.149490;0.000000;,
    0.149490;0.199227;,
    0.149490;0.199227;,
    0.300687;0.199227;,
    0.300687;0.000000;,
    0.219627;0.000000;,
    0.300687;0.000000;,
    0.300687;0.199227;,
    0.300687;0.199227;,
    0.219627;0.199227;,
    0.219627;0.000000;,
    0.302533;0.000000;,
    0.149490;0.000000;,
    0.149490;0.199227;,
    0.149490;0.199227;,
    0.302533;0.199227;,
    0.302533;0.000000;,
    0.344720;0.012168;,
    0.472597;0.012168;,
    0.487999;0.039477;,
    0.487999;0.039477;,
    0.328115;0.039477;,
    0.344720;0.012168;,
    0.438329;0.012168;,
    0.372882;0.012168;,
    0.360308;0.039477;,
    0.360308;0.039477;,
    0.456047;0.039477;,
    0.438329;0.012168;,
    0.344720;0.012168;,
    0.472597;0.012168;,
    0.487999;0.039477;,
    0.487999;0.039477;,
    0.328115;0.039477;,
    0.344720;0.012168;,
    0.372882;0.012168;,
    0.438329;0.012168;,
    0.456047;0.039477;,
    0.456047;0.039477;,
    0.360308;0.039477;,
    0.372882;0.012168;,
    0.485730;0.456020;,
    0.005050;0.456025;,
    0.005051;0.622220;,
    0.005051;0.622220;,
    0.485731;0.622215;,
    0.485730;0.456020;,
    0.485730;0.455962;,
    0.219105;0.455965;,
    0.219106;0.622160;,
    0.219106;0.622160;,
    0.485731;0.622157;,
    0.485730;0.455962;,
    0.485730;0.458163;,
    0.005050;0.458168;,
    0.005051;0.624363;,
    0.005051;0.624363;,
    0.485731;0.624358;,
    0.485730;0.458163;,
    0.485730;0.455982;,
    0.219105;0.455984;,
    0.219106;0.622179;,
    0.219106;0.622179;,
    0.485731;0.622177;,
    0.485730;0.455982;,
    0.364851;0.793299;,
    0.462051;0.793299;,
    0.462051;0.722543;,
    0.462051;0.722543;,
    0.364851;0.722543;,
    0.364851;0.793299;,
    0.462051;0.793299;,
    0.546331;0.793299;,
    0.546331;0.722543;,
    0.546331;0.722543;,
    0.462051;0.722543;,
    0.462051;0.793299;,
    0.113233;0.793299;,
    0.203051;0.793299;,
    0.203051;0.722543;,
    0.203051;0.722543;,
    0.113233;0.722543;,
    0.113233;0.793299;,
    0.203051;0.793299;,
    0.302097;0.793299;,
    0.302097;0.722543;,
    0.302097;0.722543;,
    0.203051;0.722543;,
    0.203051;0.793299;,
    0.615574;0.718785;,
    0.661301;0.737260;,
    0.680570;0.782657;,
    0.570177;0.738055;,
    0.615574;0.718785;,
    0.680570;0.782657;,
    0.551702;0.783781;,
    0.570177;0.738055;,
    0.680570;0.782657;,
    0.193089;0.603759;,
    0.284581;0.603759;,
    0.284581;0.506895;,
    0.284581;0.506895;,
    0.193089;0.506895;,
    0.193089;0.603759;,
    0.284581;0.603759;,
    0.376072;0.603759;,
    0.376072;0.506895;,
    0.376072;0.506895;,
    0.284581;0.506895;,
    0.284581;0.603759;,
    0.010105;0.603759;,
    0.101597;0.603759;,
    0.101597;0.506895;,
    0.101597;0.506895;,
    0.010105;0.506895;,
    0.010105;0.603759;,
    0.101597;0.603759;,
    0.193089;0.603759;,
    0.193089;0.506895;,
    0.193089;0.506895;,
    0.101597;0.506895;,
    0.101597;0.603759;,
    0.936761;0.203838;,
    0.964733;0.192251;,
    0.976318;0.164280;,
    0.908790;0.192252;,
    0.936761;0.203838;,
    0.976318;0.164280;,
    0.897203;0.164281;,
    0.908790;0.192252;,
    0.976318;0.164280;,
    0.999565;0.062518;,
    0.891206;0.062518;,
    0.999565;0.134392;,
    0.891206;0.134392;,
    0.999565;0.134392;,
    0.891206;0.062518;,
    0.300256;0.004891;,
    0.220058;0.004891;,
    0.300256;0.271856;,
    0.220058;0.271856;,
    0.300256;0.271856;,
    0.220058;0.004891;,
    0.220058;0.004891;,
    0.300256;0.004891;,
    0.220058;0.271856;,
    0.300256;0.271856;,
    0.220058;0.271856;,
    0.300256;0.004891;,
    0.300256;0.004891;,
    0.220058;0.004891;,
    0.300256;0.271856;,
    0.220058;0.271856;,
    0.300256;0.271856;,
    0.220058;0.004891;,
    0.300256;0.004891;,
    0.220058;0.004891;,
    0.300256;0.271856;,
    0.220058;0.271856;,
    0.300256;0.271856;,
    0.220058;0.004891;,
    0.999565;0.062518;,
    0.891206;0.062518;,
    0.891206;0.134392;,
    0.891206;0.134392;,
    0.999565;0.134392;,
    0.999565;0.062518;,
    0.300256;0.004891;,
    0.220058;0.004891;,
    0.220058;0.271856;,
    0.220058;0.271856;,
    0.300256;0.271856;,
    0.300256;0.004891;,
    0.300256;0.004891;,
    0.220058;0.004891;,
    0.220058;0.271856;,
    0.220058;0.271856;,
    0.300256;0.271856;,
    0.300256;0.004891;,
    0.220058;0.004891;,
    0.300256;0.004891;,
    0.300256;0.271856;,
    0.300256;0.271856;,
    0.220058;0.271856;,
    0.220058;0.004891;,
    0.220058;0.004891;,
    0.300256;0.004891;,
    0.300256;0.271856;,
    0.300256;0.271856;,
    0.220058;0.271856;,
    0.220058;0.004891;,
    0.487999;0.012168;,
    0.458518;0.012168;,
    0.446240;0.039477;,
    0.446240;0.039477;,
    0.487999;0.039477;,
    0.487999;0.012168;,
    0.434524;0.012168;,
    0.487999;0.012168;,
    0.487999;0.039477;,
    0.487999;0.039477;,
    0.416709;0.039477;,
    0.434524;0.012168;,
    0.487999;0.012168;,
    0.458518;0.012168;,
    0.446240;0.039477;,
    0.446240;0.039477;,
    0.487999;0.039477;,
    0.487999;0.012168;,
    0.458518;0.012168;,
    0.487999;0.012168;,
    0.487999;0.039477;,
    0.487999;0.039477;,
    0.446240;0.039477;,
    0.458518;0.012168;,
    0.999565;0.062518;,
    0.891206;0.062518;,
    0.999565;0.134392;,
    0.891206;0.134392;,
    0.999565;0.134392;,
    0.891206;0.062518;,
    0.300256;0.004891;,
    0.220058;0.004891;,
    0.300256;0.271856;,
    0.220058;0.271856;,
    0.300256;0.271856;,
    0.220058;0.004891;,
    0.220058;0.004891;,
    0.300256;0.004891;,
    0.220058;0.271856;,
    0.300256;0.271856;,
    0.220058;0.271856;,
    0.300256;0.004891;,
    0.300256;0.004891;,
    0.220058;0.004891;,
    0.300256;0.271856;,
    0.220058;0.271856;,
    0.300256;0.271856;,
    0.220058;0.004891;,
    0.300256;0.004891;,
    0.220058;0.004891;,
    0.300256;0.271856;,
    0.220058;0.271856;,
    0.300256;0.271856;,
    0.220058;0.004891;,
    0.487999;0.012168;,
    0.458518;0.012168;,
    0.446240;0.039477;,
    0.446240;0.039477;,
    0.487999;0.039477;,
    0.487999;0.012168;,
    0.434524;0.012168;,
    0.487999;0.012168;,
    0.487999;0.039477;,
    0.487999;0.039477;,
    0.416709;0.039477;,
    0.434524;0.012168;,
    0.487999;0.012168;,
    0.458518;0.012168;,
    0.446240;0.039477;,
    0.446240;0.039477;,
    0.487999;0.039477;,
    0.487999;0.012168;,
    0.458518;0.012168;,
    0.487999;0.012168;,
    0.487999;0.039477;,
    0.487999;0.039477;,
    0.446240;0.039477;,
    0.458518;0.012168;,
    0.836759;0.380429;,
    0.829070;0.380429;,
    0.833217;0.593043;,
    0.828882;0.380592;,
    0.832748;0.380592;,
    0.836895;0.594552;,
    0.836895;0.594552;,
    0.833029;0.594552;,
    0.828882;0.380592;,
    0.826276;0.380673;,
    0.836821;0.380673;,
    0.833926;0.592492;,
    0.833029;0.594552;,
    0.836895;0.594552;,
    0.828882;0.380592;,
    0.836759;0.380429;,
    0.829070;0.380429;,
    0.833217;0.593043;,
    0.828882;0.380592;,
    0.832748;0.380592;,
    0.836895;0.594552;,
    0.836895;0.594552;,
    0.833029;0.594552;,
    0.828882;0.380592;,
    0.826276;0.380673;,
    0.836821;0.380673;,
    0.833926;0.592492;,
    0.833029;0.594552;,
    0.836895;0.594552;,
    0.828882;0.380592;,
    0.836759;0.380429;,
    0.829070;0.380429;,
    0.833217;0.593043;,
    0.828882;0.380592;,
    0.832748;0.380592;,
    0.836895;0.594552;,
    0.836895;0.594552;,
    0.833029;0.594552;,
    0.828882;0.380592;,
    0.826276;0.380673;,
    0.836821;0.380673;,
    0.833926;0.592492;,
    0.833029;0.594552;,
    0.836895;0.594552;,
    0.828882;0.380592;;
   }
  }
 }
}