{
  "targets": [
    {
      "target_name": "discord_game",
      "sources": [
        "src/discord_game.c",
        "src/application.c",
        "src/activity.c"
      ],

      "include_dirs": [
        "include/",
        "sdk/"
      ],
      "conditions": [
        ["OS == 'win'", {
          "conditions": [
            ["target_arch == 'ia32'", {
              "link_settings": {
                "libraries": [
                  "<(module_root_dir)/sdk/x86/discord_game_sdk.dll.lib"
                ],
                "copies":[{
                  "destination":"<(module_root_dir)/build/Release",
                  "files":["<(module_root_dir)/sdk/x86/discord_game_sdk.dll"]
                }]
              }
            }],
            ["target_arch == 'x64'", {
              "link_settings": {
                "libraries": [
                  "<(module_root_dir)/sdk/x86_64/discord_game_sdk.dll.lib"
                ],
                "copies":[{
                  "destination":"<(module_root_dir)/build/Release",
                  "files":["<(module_root_dir)/sdk/x86_64/discord_game_sdk.dll"]
                }]
              }
            }]
          ]
        }],
        ["OS == 'mac'", {
          "link_settings": {
            "libraries": [
              "-Wl,-rpath,<(module_root_dir)/sdk/x86_64",
              "-Wl,-rpath,@executable_path/../Resources",
              "-Wl,-rpath,@executable_path/../Frameworks",
              "<(module_root_dir)/sdk/x86_64/discord_game_sdk.dylib"
            ]
          }
        }]
      ]
    }
  ]
}
