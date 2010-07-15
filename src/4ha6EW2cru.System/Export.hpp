#   ifdef __GNUC__
#     define GAMEAPI 
#   endif
#   ifdef MSVC
#     ifdef EXPORT
#      define GAMEAPI __declspec(dllexport)
#     else
#       define GAMEAPI __declspec(dllimport)
#     endif
#   endif
  