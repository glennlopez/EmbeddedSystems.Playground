var group__wlan =
[
    [ "slSmartConfigStartAsyncResponse_t", "structsl_smart_config_start_async_response__t.html", [
      [ "private_token", "group__wlan.html#gae4b4f8fdf1977f0267d37f00afaf0d6d", null ],
      [ "private_token_len", "group__wlan.html#ga1b3175f8dbe2500c7a5f0cbc14db6932", null ],
      [ "ssid", "group__wlan.html#ga18d6c322c89b9482d88f4d1b151e1208", null ],
      [ "ssid_len", "group__wlan.html#gac38a6dd697930374a885f5f1c9421640", null ],
      [ "status", "group__wlan.html#ga9c2e24094c936ef0862eb44b30afedf2", null ]
    ] ],
    [ "slSmartConfigStopAsyncResponse_t", "structsl_smart_config_stop_async_response__t.html", [
      [ "padding", "group__wlan.html#ga201aa5283495b87fc8832e9baa63aad5", null ],
      [ "status", "group__wlan.html#ga724f8cf1b8ff3d96c3a9cbcd2a6957a6", null ]
    ] ],
    [ "slWlanConnFailureAsyncResponse_t", "structsl_wlan_conn_failure_async_response__t.html", [
      [ "padding", "group__wlan.html#ga201aa5283495b87fc8832e9baa63aad5", null ],
      [ "status", "group__wlan.html#ga724f8cf1b8ff3d96c3a9cbcd2a6957a6", null ]
    ] ],
    [ "sl_protocol_wlanConnectAsyncResponse_t", "structsl__protocol__wlan_connect_async_response__t.html", [
      [ "bssid", "group__wlan.html#gafe5aa2d29b976557a88eab996244aedc", null ],
      [ "connection_type", "group__wlan.html#ga6173247e0adaa2b1a8e4cf0b338cb826", null ],
      [ "go_peer_device_name", "group__wlan.html#ga40f12accd1196f2ac05d3511c4ed49c7", null ],
      [ "go_peer_device_name_len", "group__wlan.html#ga37da28c0a7da334948501d79c9d903cb", null ],
      [ "padding", "group__wlan.html#ga9753c7c72915aa208119266b2338ea10", null ],
      [ "reason_code", "group__wlan.html#gaeb11e431f2cddfaebd37e8739263d647", null ],
      [ "ssid_len", "group__wlan.html#ga340f18f235799c8c8b592c782ef1c079", null ],
      [ "ssid_name", "group__wlan.html#ga6fd6d9217a47e240b9d454860ed8511b", null ]
    ] ],
    [ "slPeerInfoAsyncResponse_t", "structsl_peer_info_async_response__t.html", [
      [ "go_peer_device_name", "group__wlan.html#ga40f12accd1196f2ac05d3511c4ed49c7", null ],
      [ "go_peer_device_name_len", "group__wlan.html#ga37da28c0a7da334948501d79c9d903cb", null ],
      [ "mac", "group__wlan.html#ga0fc1ebcb690ec8426f156a7fd33e0913", null ],
      [ "own_ssid", "group__wlan.html#ga4ece6807aa2ca2a602290b8a6572f3dc", null ],
      [ "own_ssid_len", "group__wlan.html#ga54cb050f627df75b2b9deda10be8a4f6", null ],
      [ "padding", "group__wlan.html#ga351940bc24af2f72269743e35b9a32c4", null ],
      [ "wps_dev_password_id", "group__wlan.html#ga531d4129dd6d5f9fe242faa30d04c45c", null ]
    ] ],
    [ "SlWlanEventData_u", "union_sl_wlan_event_data__u.html", [
      [ "APModeStaConnected", "group__wlan.html#ga8a4b774d3fea5bd36d46e36326f11ed4", null ],
      [ "APModestaDisconnected", "group__wlan.html#ga5e285baad857f73a0167f73e4b17ae50", null ],
      [ "P2PModeDevFound", "group__wlan.html#ga8b490ba7a54396f6e289b5789644de5f", null ],
      [ "P2PModeNegReqReceived", "group__wlan.html#gaee4d526e0489f6384555d71c6a4c2ff3", null ],
      [ "P2PModewlanConnectionFailure", "group__wlan.html#ga2211e22e568ee4349eebd7ed5b6f9b60", null ],
      [ "smartConfigStartResponse", "group__wlan.html#ga3e0a9eb580163ca72c178d96a5edba79", null ],
      [ "smartConfigStopResponse", "group__wlan.html#ga962b4e0845dd71daaf9929aea34183fc", null ],
      [ "STAandP2PModeDisconnected", "group__wlan.html#ga4637b8a9af931f76f3e812be67833fa2", null ],
      [ "STAandP2PModeWlanConnected", "group__wlan.html#gaee13bfd19fdf5ab9c25c9a0f77b57612", null ]
    ] ],
    [ "SlWlanEvent_t", "struct_sl_wlan_event__t.html", [
      [ "Event", "group__wlan.html#ga82b85c0f983cb4be38dde9fba5968f46", null ],
      [ "EventData", "group__wlan.html#gae587c51197255d4e4ef20cc90d73825f", null ]
    ] ],
    [ "SlGetRxStatResponse_t", "struct_sl_get_rx_stat_response__t.html", [
      [ "AvarageDataCtrlRssi", "group__wlan.html#gaefd98349f088e3d291d804d6ba0b3d48", null ],
      [ "AvarageMgMntRssi", "group__wlan.html#ga2e5e0ffb3b3d82d50c2ada5eabadda1d", null ],
      [ "GetTimeStamp", "group__wlan.html#ga006d3719d624e11eaa3cd1d3322f75e9", null ],
      [ "RateHistogram", "group__wlan.html#ga0a6ca65f911e49a8783217077acd1983", null ],
      [ "ReceivedFcsErrorPacketsNumber", "group__wlan.html#ga038e3b24286400fa0cd6c3a8b140f4b5", null ],
      [ "ReceivedPlcpErrorPacketsNumber", "group__wlan.html#ga95b8db41b7186377db1ba339fb82575a", null ],
      [ "ReceivedValidPacketsNumber", "group__wlan.html#ga91c1cfc333fa258db90d65de266b357e", null ],
      [ "RssiHistogram", "group__wlan.html#ga2fb3a6dd9e0b2c60a5fa3ca36b7ce291", null ],
      [ "StartTimeStamp", "group__wlan.html#gae04f4c694033e567028a01bd71ddd032", null ]
    ] ],
    [ "Sl_WlanNetworkEntry_t", "struct_sl___wlan_network_entry__t.html", [
      [ "bssid", "group__wlan.html#ga6a3e9db687574fe89cdc84abd2fd2645", null ],
      [ "reserved", "group__wlan.html#ga7a0c313f9a023fb215e2106a6a4dac75", null ],
      [ "rssi", "group__wlan.html#ga0e8c2d628a681a89f8924f264401989a", null ],
      [ "sec_type", "group__wlan.html#ga695e3013977198a85eaaa280d6e0d2d2", null ],
      [ "ssid", "group__wlan.html#ga31cc200715c95a80075e225cabb62911", null ],
      [ "ssid_len", "group__wlan.html#ga340f18f235799c8c8b592c782ef1c079", null ]
    ] ],
    [ "SlSecParams_t", "struct_sl_sec_params__t.html", [
      [ "Key", "group__wlan.html#ga08ad9767ce01da65879eedff503dbfff", null ],
      [ "KeyLen", "group__wlan.html#gaeb6f1a41fb682dc06cfdc1d0c1bef18f", null ],
      [ "Type", "group__wlan.html#gaa8450776ab620f8870aaee14ac1747fe", null ]
    ] ],
    [ "SlSecParamsExt_t", "struct_sl_sec_params_ext__t.html", [
      [ "AnonUser", "group__wlan.html#gaed01740e7be53b6ec43a6b3e0e011b9a", null ],
      [ "AnonUserLen", "group__wlan.html#ga46595900758e5eea2e6dcb396f65f7e8", null ],
      [ "CertIndex", "group__wlan.html#gac7dd5ef84298a6583c14cf826cd2289f", null ],
      [ "EapMethod", "group__wlan.html#gadec626c3ddd6f52858e7c2ff3fe56cb6", null ],
      [ "User", "group__wlan.html#ga0e5a29a37f14394daf3df9b9e56a9f2c", null ],
      [ "UserLen", "group__wlan.html#ga363b9a9d0656d0c97ff735422e0ff1c0", null ]
    ] ],
    [ "SlGetSecParamsExt_t", "struct_sl_get_sec_params_ext__t.html", [
      [ "AnonUser", "group__wlan.html#ga018057b0083c446b838740d48da05d2d", null ],
      [ "AnonUserLen", "group__wlan.html#ga46595900758e5eea2e6dcb396f65f7e8", null ],
      [ "CertIndex", "group__wlan.html#gac7dd5ef84298a6583c14cf826cd2289f", null ],
      [ "EapMethod", "group__wlan.html#gadec626c3ddd6f52858e7c2ff3fe56cb6", null ],
      [ "User", "group__wlan.html#ga1f62c2d9596765904365ac1626e95788", null ],
      [ "UserLen", "group__wlan.html#ga363b9a9d0656d0c97ff735422e0ff1c0", null ]
    ] ],
    [ "slWlanScanParamCommand_t", "structsl_wlan_scan_param_command__t.html", [
      [ "G_Channels_mask", "group__wlan.html#gaa125a7dc938f0ba1674fc2f52a40b4a3", null ],
      [ "rssiThershold", "group__wlan.html#ga2d8588fba0893b9590e3c4a1cf40735f", null ]
    ] ],
    [ "sl_protocol_InfoElement_t", "structsl__protocol___info_element__t.html", [
      [ "data", "group__wlan.html#gae5c081c43ad642766eefaf6219ad9588", null ],
      [ "id", "group__wlan.html#ga35fc2aadb5f638d5cc76810431d956c7", null ],
      [ "length", "group__wlan.html#ga92fb67cb6d873cedc8c09a2d901396a2", null ],
      [ "oui", "group__wlan.html#gaac7520636fd1fb014683185c68890314", null ]
    ] ],
    [ "sl_protocol_WlanSetInfoElement_t", "structsl__protocol___wlan_set_info_element__t.html", [
      [ "ie", "group__wlan.html#gac1029492d0e3b06663e3dfa879773e2a", null ],
      [ "index", "group__wlan.html#ga5abc5420a7f15af7410173395b610ea8", null ],
      [ "role", "group__wlan.html#gabd416002fb5c1d79fddbb76916d343be", null ]
    ] ],
    [ "sl_WlanConnect", "group__wlan.html#ga2f3666868048a94e8b80f4699bcec3e3", null ],
    [ "sl_WlanDisconnect", "group__wlan.html#ga51789d863facb9fa0a1dc79e1680c685", null ],
    [ "sl_WlanGet", "group__wlan.html#gada88513a524d384635ea74b6ebab0e2b", null ],
    [ "sl_WlanGetNetworkList", "group__wlan.html#gaf4c298abe8d715c9bb82e70c32de747e", null ],
    [ "sl_WlanPolicyGet", "group__wlan.html#ga5bb7b228eac6110849f392c3a1b233a0", null ],
    [ "sl_WlanPolicySet", "group__wlan.html#ga43fc393a4a981eb2d6340e5aaf954203", null ],
    [ "sl_WlanProfileAdd", "group__wlan.html#ga79cc03e49a1388e360964e091b54ee61", null ],
    [ "sl_WlanProfileDel", "group__wlan.html#gaf86d6970b54fc772a1b10ebf47375955", null ],
    [ "sl_WlanProfileGet", "group__wlan.html#ga17cb00c9f57a6cd53a6346f67c0fc093", null ],
    [ "sl_WlanRxFilterAdd", "group__wlan.html#ga0f61489aecc77c79f5350a8c6bab3ab5", null ],
    [ "sl_WlanRxFilterGet", "group__wlan.html#ga425b33c0a66b7567bdc06f162234a309", null ],
    [ "sl_WlanRxFilterSet", "group__wlan.html#gaefbc2f3fd8ed675dc8d0bdd4c201205d", null ],
    [ "sl_WlanRxStatGet", "group__wlan.html#ga177dfdb0f153fa56d8d9dbb64016c97e", null ],
    [ "sl_WlanRxStatStart", "group__wlan.html#ga98bdd9b069df218eecf617b83c87b8e7", null ],
    [ "sl_WlanRxStatStop", "group__wlan.html#ga455284a9c7cad663d417fc5536fa31e6", null ],
    [ "sl_WlanSet", "group__wlan.html#gab144133b7db84bc8c75e3c97bad42b9b", null ],
    [ "sl_WlanSetMode", "group__wlan.html#ga39fc3e79d0444f2fa47f76d5cfef3a95", null ],
    [ "sl_WlanSmartConfigStart", "group__wlan.html#gaf6dfee1f2db609421f3f2bf00a1599f3", null ],
    [ "sl_WlanSmartConfigStop", "group__wlan.html#ga8e7ed9492ceff9f6afe811d1b07dd711", null ]
];