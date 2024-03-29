
#include "my_lib01.h"

//declared as const to save compile and execution time/space
const unsigned char my_lib01[] = 
{

//0: the void [3f8f3df0-c1ed-49b9-bf8b-17829af3ec15]
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
//1: wood L [158a2736-a8e4-4d3a-8be4-67fa52c6f158]
0xFF,0xFF,0x80,0x80,0xEF,0x90,0x80,0xFF,0xFF,0xFF,0x80,0x80,0xFD,0x82,0x80,0xFF,
//2: wood mid [b38953e9-c2d0-428c-87b0-371101b84aeb]
0xFF,0xFF,0x00,0x00,0xDF,0x20,0x00,0xFF,0xFF,0xFF,0x00,0x00,0xFB,0x04,0x00,0xFF,
//3: wood R [11dfe096-c756-4f48-b6a6-d6f5fb03c5cd]
0xFF,0xFF,0x01,0x01,0xDF,0x21,0x01,0xFF,0xFF,0xFF,0x01,0x01,0xF7,0x09,0x01,0xFF,
//4: sea 1 [23b8adbd-b9d4-4472-8aeb-a5b7ec8f979c]
0x03,0x00,0x9C,0x03,0x60,0x1C,0x81,0x60,0x4E,0x81,0x18,0x87,0x30,0x0F,0x7C,0x03,
//5: sea 2 [40f6c4af-01ec-4933-8c23-852890842fbf]
0xC0,0x00,0x3A,0xC0,0x0F,0x30,0xC1,0x0E,0x60,0x80,0x1F,0xE0,0x0C,0xF3,0x3C,0xC3,
//6: sea 3 [4adc2ef7-0333-40f8-87cf-d07eb397181c]
0x13,0x00,0x3C,0x03,0xC0,0x3C,0x13,0xE0,0x0F,0x00,0xFC,0x03,0x78,0x87,0x3E,0xC1,
//7: sea 4 [7c8b8bb4-4335-4780-a1ac-f3624c12eaf0]
0xC0,0x00,0x3B,0xC0,0x06,0x38,0x81,0x06,0x72,0x81,0x18,0xE1,0x0C,0xF0,0x3E,0xC0,
//8: crystal NW [41dcfc60-d403-4a7f-ab96-f9f33c69ebba]
0x01,0x01,0x02,0x02,0x05,0x04,0x09,0x08,0xEC,0xE8,0x9E,0x98,0xCA,0x88,0xA8,0xC8,
//9: crystal SW [a33f6d92-58f6-4c2a-9026-7a7a8a4d1b94]
0x5C,0x68,0x2E,0x38,0x7B,0x79,0x9A,0x9A,0xCE,0x8A,0x6E,0x4A,0x36,0x3E,0x05,0x03,
//10: crystal NE [6647a7e6-36ca-4a64-924f-766fdf480c9e]
0x00,0x00,0x80,0x80,0x4E,0x4E,0x32,0x32,0x66,0x22,0xAE,0x62,0x2C,0xE4,0x37,0xEF,
//11: crystal SE [38485607-5be9-4b6e-99bf-60c244a8ec2a]
0x2B,0xF9,0xB1,0xF3,0x66,0x62,0x6A,0x26,0xEC,0x24,0xF4,0x2C,0xB8,0x78,0xD0,0xE0,
//12: hole NW [37278d4b-11c7-42a6-a415-0e48ecc877ae]
0x08,0x00,0x07,0x00,0x40,0x07,0x06,0x37,0x17,0x3F,0x3E,0x7F,0xEF,0x3F,0x3F,0x7F,
//13: hole SW [4446eedb-e688-4172-bca5-b949ad4541bf]
0x3F,0x7F,0x9F,0x7F,0x1F,0x1F,0x0F,0x3F,0x1F,0x0F,0x2D,0x1E,0x44,0x00,0x00,0x00,
//14: hole NE [5b37c23c-8be0-4f78-909d-e9e5fd0e35ff]
0x80,0x00,0x26,0x80,0x08,0xF0,0xC0,0xF0,0xD6,0xF0,0xFC,0xFE,0xFC,0xFE,0xF6,0xFC,
//15: hole SE [fa54bd7f-934d-482d-9928-4af1f3609171]
0xFE,0xFE,0xFC,0xFE,0xFA,0xFC,0xF0,0xF0,0xF4,0xF8,0xEE,0xE0,0x40,0x80,0x00,0x00,
//16: well NW [688c3b3d-d7c9-4b3d-97f6-e185ad6fc112]
0x07,0x07,0x18,0x18,0x27,0x27,0x5B,0x5E,0xB3,0xAE,0xA7,0xBF,0xDF,0xDF,0xE7,0xA7,
//17: well SW [574cd49d-0eec-4b81-8522-abdca47acfb3]
0xF8,0x98,0xEF,0xCF,0xB9,0xA8,0xFB,0xB8,0x67,0x67,0x2F,0x20,0x1F,0x18,0x07,0x07,
//18: well NE [9c228386-e4d2-4da3-a1d0-1bdcdc1553bb]
0xE0,0xE0,0x18,0x18,0xE4,0xE4,0x9A,0x7A,0x1D,0xF5,0xF5,0xFD,0xFB,0xFB,0xE7,0xE5,
//19: well SE [670c3764-b10b-478b-82b2-c17377a86f5c]
0x1F,0x19,0xF7,0xF3,0xFF,0x15,0xFF,0x1D,0xFE,0xE7,0x9C,0x87,0xB8,0x9E,0xE0,0xFC,
//20: sapin NW [0efbcecd-6cf6-4d0a-8733-06190cf10c1b]
0x00,0x01,0x00,0x02,0x00,0x04,0x01,0x18,0x11,0x60,0x0A,0x00,0x00,0x34,0x00,0x18,
//21: sapin SW [ef6569c3-a894-44db-903e-d0faaaaed70e]
0x04,0x10,0x09,0x64,0x10,0x28,0x02,0x11,0x0D,0x62,0x31,0x0E,0x03,0x02,0x03,0x01,
//22: sapin NE [b5f5fbc7-1438-496e-891d-5609aea76b8e]
0x00,0x80,0x80,0x40,0x80,0x60,0xC0,0x38,0xA0,0x5E,0xA0,0x7C,0x58,0x30,0x30,0x50,
//23: sapin SE [100d1ee6-85d9-4b85-93dd-96f4ab1cce00]
0x98,0x2C,0x9E,0x66,0xE0,0x3E,0x78,0x98,0x08,0xFC,0x40,0xC0,0x6C,0xF0,0x80,0xF8,
//24: palmtree NW [d174d033-f7cd-49d6-9ff7-d37e258a4118]
0x00,0x0C,0x04,0x32,0x1C,0x43,0x20,0x9D,0x47,0x30,0x0C,0x63,0x08,0x25,0x10,0x28,
//25: palmtree SW [95d13f36-706f-487e-8085-710f36dbe0b0]
0x10,0x28,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x07,0x00,0x03,
//26: palmtree NE [edf33cc3-7d5d-43e5-8dc0-1eee01459da8]
0x00,0x30,0x10,0xC8,0x78,0x04,0x8C,0x72,0x10,0x8C,0x30,0xC4,0x4C,0xB2,0x04,0xCA,
//27: palmtree SE [cd4fea88-215c-4fc4-b187-809914e15fcc]
0x00,0x64,0x20,0x40,0x00,0x60,0x20,0xC0,0x40,0x80,0x20,0xF0,0x74,0xF8,0xE8,0xF0,
//28: tower 1 [4736c7bc-28ce-45f7-b87e-3d50ee352b16]
0xFF,0xFF,0xFF,0xA4,0xA4,0xFF,0xA4,0xFF,0xFF,0xFF,0xFF,0x91,0x93,0xFD,0x93,0xFD,
//29: tower 2 [f1e04c83-a224-4e49-9f42-65bf854dedbf]
0xFF,0xFF,0xF8,0x20,0x35,0xEA,0x2B,0xF4,0xFF,0xFF,0xE6,0x04,0xAF,0x54,0x9F,0x64,
//30: tower 3 [b97ac2e2-4212-4000-a153-8d57f11e3a61]
0xFF,0xFF,0x40,0x40,0xD7,0x40,0xFF,0x40,0xFF,0xFF,0x08,0x08,0x7B,0x08,0xFF,0x08,
//31: tower 4 [172e2a0e-63e8-41f7-a510-6215aec1a009]
0xFF,0xFF,0x1F,0x04,0xEC,0x17,0xD4,0x2F,0xFF,0xFF,0x67,0x20,0xF4,0x2B,0xFA,0x25,
//32: tower 5 [05d4c520-3c30-4487-9344-6e3f8243e13c]
0xFF,0xFF,0xF5,0x2F,0x25,0xFF,0x25,0xFF,0xFF,0xFF,0xE9,0x9F,0xC9,0xBF,0xC9,0xBF,
//33: rock NW [a6c83eab-05ae-4728-914d-49be8504c0a7]
0x01,0x01,0x03,0x03,0x0E,0x0C,0x1E,0x10,0x32,0x24,0x60,0x63,0xC4,0xC3,0x88,0x84,
//34: rock SW [3189a0b6-7613-4564-a01f-5f08039e0628]
0xD8,0x84,0xB8,0xC8,0x88,0xF8,0xD0,0xF0,0x58,0x70,0x77,0x78,0x18,0x1F,0x0F,0x0F,
//35: rock NE [db168831-e3bd-4a1e-b808-b54330826b92]
0xF0,0xF0,0x98,0x18,0x0C,0x04,0x0E,0x12,0x26,0x1A,0x47,0x29,0x41,0x8F,0x03,0x43,
//36: rock SE [b2a88ec0-67c5-40a2-9a2c-61ecbeeaf29d]
0x03,0x21,0x11,0x23,0x4F,0x33,0x41,0x3F,0xE2,0x5E,0x66,0xDF,0x8C,0xFF,0xF8,0xFE,
//37: column NW [37767a78-d754-44ca-baed-5193bd7745bd]
0x8B,0x80,0x8B,0x80,0x8B,0x80,0x8B,0x80,0x8B,0x80,0x8B,0x80,0x8B,0x80,0x8B,0x80,
//38: column SW [c4970105-badf-458b-aa8b-ef5e69a5427b]
0x8B,0xC0,0x8B,0xB0,0x83,0x8C,0x88,0x93,0xCB,0x40,0x3A,0x31,0x0F,0x0C,0x03,0x03,
//39: column NE [91466e04-1c7a-434a-a261-3175081898b0]
0xA1,0x5F,0xA1,0x5F,0xA1,0x5F,0xA1,0x5F,0xA1,0x5F,0xA1,0x5F,0xA1,0x5F,0xA1,0x5F,
//40: column SE [2a14243b-2d51-45c1-980c-04d30b986530]
0xA3,0x5F,0xAD,0x5F,0xB1,0x7F,0x29,0xDF,0xA3,0x5E,0xAF,0x5C,0xBC,0x70,0xC0,0xC0,
//41: empty [0bc07258-9774-4026-ba94-17fa771ad708]
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//42: grass 1 [b840009d-130f-434c-91fb-4fce521d6883]
0x00,0x00,0x00,0x00,0x10,0x00,0x54,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//43: grass 2 [dce14fa9-cc1f-49a5-a667-1baf2e46f7fb]
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0xA4,0x00,0x00,0x00,
//44: sand [fba2ebac-8d79-40d1-acbc-d35afeab389b]
0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x40,0x04,0x00,0x00,0x00,
//45: arbalette [08910d81-dfce-44dd-b257-06eb5159a4e4]
0x1E,0x3E,0x72,0x78,0x72,0xF0,0xFA,0xF8,0x9E,0xDC,0x9E,0x8C,0xFE,0x82,0x03,0x01,
//46: coffre NW [11e494c8-59e2-4b7d-afab-3a4919d2793a]
0x1F,0x1F,0x3F,0x25,0x7F,0x5B,0xFF,0xB7,0xFF,0xB7,0xFF,0xB7,0xEB,0x9C,0xE3,0xFF,
//47: coffre SW [ab341f9e-ce84-4183-bd4c-1be6aca66b79]
0xDC,0xB7,0xFF,0xB7,0xFF,0xB7,0xFF,0xB7,0xBF,0xC0,0xFF,0xFF,0x00,0x00,0x00,0x00,
//48: coffre NE [eb98ba86-99be-4d50-87ba-210d710c84e5]
0xF0,0xF0,0xF8,0x08,0xFC,0xB4,0xFC,0x74,0xFC,0x6C,0xFC,0x54,0xEC,0x34,0xDC,0xF4,
//49: coffre SE [3d868927-dd78-48fa-b7db-46fe2e295a2e]
0xBC,0x74,0xF4,0x7C,0xFE,0x6E,0xFF,0x5F,0x3E,0xFE,0xF8,0xF8,0x00,0x00,0x00,0x00,
//50: door NW [503529ba-e083-49f2-88c4-68c2ea93d26b]
0x0F,0x0F,0x35,0x3A,0x4D,0x72,0x6D,0x52,0xAC,0xD3,0xAD,0xD2,0xAD,0xD2,0xBC,0xDB,
//51: door SW [0701a09f-7606-47af-a6e8-a9b8d85c111e]
0xA5,0xE6,0xDB,0xDA,0xDB,0xCA,0xA5,0xE6,0xBD,0xDA,0xAD,0xD2,0x80,0xFF,0xFF,0xFF,
//52: door NE [54a3dc03-e94d-499e-8e5c-3355578e683e]
0xF0,0xF0,0xAC,0x5C,0xB2,0x4E,0xB6,0x4A,0xB5,0x4B,0xA5,0x5B,0xB5,0x4B,0xB5,0x4B,
//53: door SE [39decba4-d20b-4f78-b1d3-4267d95a70c7]
0xB5,0x4C,0xB3,0x4F,0x31,0xCF,0xA5,0x5C,0xB3,0x4F,0xB5,0x4B,0x01,0xFF,0xFF,0xFF,
//54: pentagram NW [babf5dfe-dfe8-47cc-9d9c-78c5f05f9264]
0xE1,0xE1,0x9F,0x9E,0x85,0xA7,0x59,0x59,0x5F,0x5C,0x6F,0x6B,0x4F,0x66,0xFD,0xB7,
//55: pentagram SW [95358afc-fc76-49f7-9f74-b41de10755c5]
0xFF,0xB5,0x4E,0x67,0x6F,0x6B,0x5F,0x5C,0x59,0x59,0x85,0xA7,0x9F,0x9E,0xE1,0xE1,
//56: pentagram NE [51251dd7-39f9-4306-8dc0-d860782b07e6]
0x87,0x87,0xF9,0x79,0xA1,0xE5,0x9A,0x9A,0xFA,0x3A,0xF6,0xD6,0x72,0xE6,0xFF,0xAD,
//57: pentagram SE [5e713583-9677-4361-9b8e-31cce4224bde]
0xBF,0xED,0xF2,0x66,0xF6,0xD6,0xFA,0x3A,0x9A,0x9A,0xA1,0xE5,0xF9,0x79,0x87,0x87,
//58: stairs up NW [8838f7a6-b630-46ab-a291-69e255cf5ac6]
0x00,0x00,0x03,0x03,0x1E,0x1E,0xF6,0xF2,0xBA,0x96,0xDA,0xB6,0xDA,0xB6,0xDA,0xB6,
//59: stairs up SW [988b881b-fa86-41a2-80f3-ed1341c1e3fb]
0xDA,0xB6,0xDA,0xB6,0xDA,0xB6,0xDA,0xB6,0xDA,0xB6,0xDB,0xB7,0xDE,0xBF,0xFF,0xFF,
//60: stairs up NE [e8ee79d6-4e19-44d2-9616-bdf5bec22a6f]
0x3F,0x3F,0xE1,0xE1,0x6F,0x21,0xAF,0x61,0xAF,0x61,0xAF,0x61,0xAF,0x61,0xAF,0x61,
//61: stairs up SE [8dfc8d56-d989-4034-a615-e15f0dc92d97]
0xAF,0x61,0xAF,0x61,0xAF,0x61,0xAF,0x61,0xBF,0x7F,0xE1,0xFF,0x01,0xFF,0xFF,0xFF,
//62: table NW [9cfdc307-3169-4c8b-b710-350315f631a3]
0x77,0x07,0x98,0x18,0x3D,0x20,0x40,0x40,0x40,0x40,0x87,0x80,0xE0,0x80,0xC0,0xC0,
//63: table SW [e3bd08b6-9b49-4659-8a59-b60bb0a62451]
0xC0,0xC0,0xFF,0xA0,0xF8,0xD8,0xBF,0xE7,0xFF,0x98,0xFF,0xBF,0xBF,0xBF,0xF1,0xF0,
//64: table NE [9b8feb7f-10ff-44dc-8d58-2e84547bbb09]
0xE1,0xE0,0x18,0x18,0x85,0x04,0x03,0x02,0x02,0x02,0x7F,0x01,0x01,0x01,0x1F,0x03,
//65: table SE [92051d42-b1c3-43d1-8a91-8b2caa27e958]
0x03,0x03,0xA7,0x05,0x1F,0x1B,0xFD,0xE7,0xFF,0x19,0xFF,0xFD,0xFD,0xFD,0x9F,0x07,
//66: stairs down NW [a56232cc-df5e-4548-b428-3e8424db61b2]
0x00,0xFF,0x7F,0xFF,0x7F,0xBF,0x71,0xA1,0x71,0xA1,0x59,0x91,0x59,0x91,0x59,0x91,
//67: stairs down SW [e2309d37-7efd-40f4-a419-ca523fb95d9a]
0x4D,0x89,0x4D,0x89,0x4D,0x89,0x47,0x85,0x47,0x85,0x47,0x85,0x7F,0xFF,0x00,0xFF,
//68: stairs down NE [ad7da548-0b3e-4f13-b01c-0ec27f0b4e86]
0x00,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0x7E,0xBF,0x7E,0x8F,0x7E,0x8F,
//69: stairs down SE [a3ca3b42-129e-42ab-ae37-1ab6c929f8f8]
0x7E,0x9F,0x76,0x9F,0x66,0xBB,0x6E,0xB3,0x4E,0xF7,0x5E,0xEF,0xFE,0xFF,0x00,0xFF,
//70: marble stele NW [3ba5444b-18d4-4bb8-9ab5-43485003adbc]
0x7F,0x0F,0x90,0x10,0x2F,0x30,0x51,0x4E,0xA4,0x9B,0xBF,0x80,0xA2,0x9D,0xAA,0x95,
//71: marble stele SW [8be9f9fe-58d8-467b-b0cd-3a4bcc2d5180]
0xE7,0x98,0xBA,0xC5,0xA2,0x9D,0xA6,0x99,0x9F,0x80,0x80,0xFF,0xA6,0xFF,0x7F,0xFF,
//72: marble stele NE [d57c8b4c-3645-4b88-86ed-dc4139968a62]
0xF1,0xF0,0x98,0x08,0xFD,0x04,0x37,0xCA,0x43,0xBD,0xF7,0x09,0x8B,0x75,0x5B,0xA7,
//73: marble stele SE [2cb961fe-360f-4cc2-984e-7d08c33e5d62]
0xF3,0x0D,0x8F,0x71,0x57,0xAB,0xD3,0x2D,0xFF,0x01,0x01,0xFF,0x11,0xFF,0xFF,0xFF,
//74: weapon wall NW [9b5fd481-1985-4f72-a0a9-e504ec9864ec]
0xFF,0xFF,0xB0,0x90,0x9E,0x8E,0xCF,0xC6,0xA6,0xA3,0xB3,0xB1,0xBD,0xBB,0xBE,0xBE,
//75: weapon wall SW [46f14eb1-185e-4b5a-937a-6a666c7996a7]
0xBC,0xBC,0x79,0x58,0x73,0x51,0xA6,0xE3,0xAF,0xE6,0x7E,0x7A,0xA6,0xFC,0xDF,0xDB,
//76: weapon wall NE [8b713430-1894-4dcc-9edc-1bb98a4ff328]
0xFF,0xFF,0xF9,0x09,0xF3,0x71,0xE7,0x63,0x4F,0xC5,0x9F,0x8D,0x3F,0x1D,0x7F,0x3D,
//77: weapon wall SE [96531e6b-eb9f-4389-85a4-9cbed5a3a85d]
0xFF,0x7D,0xDE,0xFA,0xBE,0xCA,0x65,0xC7,0xF5,0x67,0xFE,0x5E,0xE5,0x3F,0xFF,0xDB,
//78: torch NW [abd4f0f7-53c9-48d5-b896-ccd70f3a6fdc]
0x72,0x00,0x8C,0x00,0x05,0x05,0x07,0x07,0x06,0x03,0x0D,0x06,0x15,0x06,0xEC,0x0F,
//79: torch SW [17950b03-2307-4a14-9524-b8916bade789]
0x4F,0x0B,0x4B,0x09,0x44,0x04,0xE7,0x07,0x7F,0x02,0x37,0x05,0x27,0x04,0x23,0x03,
//80: torch NE [72432137-e4a9-4d56-8238-3fabd9cd5ede]
0x70,0x40,0xA0,0x80,0xA1,0x80,0xB3,0x80,0xCE,0xC0,0x66,0xE0,0xA3,0x60,0x74,0xF0,
//81: torch SE [d6341d97-ee93-4c6d-8f39-856806fdb942]
0x78,0xD0,0xD0,0x90,0x20,0x38,0xE3,0xFC,0xC2,0x7C,0xE0,0xBC,0xE0,0x38,0xCE,0xF0,
//82: skeleton NW [c52c5b53-314a-46ad-b615-127235e7de39]
0x03,0x03,0x07,0x04,0x0F,0x08,0x0F,0x0B,0x0F,0x0B,0x1E,0x1B,0x37,0x2C,0x17,0x1D,
//83: skeleton SW [f1e40567-ed2a-4f7a-a793-bdf42241d3c6]
0x2B,0x3B,0x2F,0x3C,0x13,0x13,0x0D,0x0C,0x13,0x1F,0x12,0x1E,0x21,0x3F,0x3F,0x3F,
//84: skeleton NE [86a746b4-eefe-41b5-9f60-9ee016baaa48]
0xE0,0xE0,0x90,0x70,0xE8,0x18,0xF8,0x68,0xF8,0x68,0xBE,0x6E,0xF7,0x19,0xF6,0x5E,
//85: skeleton SE [0f391d02-4dd8-4539-a8fc-75a496b009da]
0xEF,0xED,0xF9,0x1F,0x69,0xEF,0x56,0x96,0xE8,0xF8,0x44,0x7C,0xFE,0xFE,0x80,0x80,
//86: wmage NW [64f83a50-c20e-4898-be2d-653e2b82beb5]
0x03,0x03,0x07,0x04,0x0F,0x08,0x1F,0x13,0x3C,0x27,0x78,0x4F,0x7F,0x5E,0x7F,0x5A,
//87: wmage SW [30ed61b2-c52e-4c5c-919b-bbdcef573199]
0x3F,0x2A,0x67,0x5C,0xDB,0xBF,0xBF,0xE4,0xBF,0xE4,0x96,0xFF,0x4F,0x79,0x3F,0x3F,
//88: wmage NE [26d6375b-af3a-4ef1-9542-ff0591dd8fbc]
0xC0,0xC0,0xE0,0x20,0xF0,0x10,0xF8,0xC8,0x3C,0xE4,0xBE,0x72,0xFE,0xDA,0xFE,0x7A,
//89: wmage SE [76b436fb-97aa-4634-9ce4-174e188fe783]
0xFC,0x54,0xFE,0x22,0xF9,0xDF,0xFD,0x27,0xFD,0x27,0xB9,0x5F,0x0A,0xFE,0xFC,0xFC,
//90: girl NW [088574a0-57f3-4709-8c02-5b44785fa8c8]
0x03,0x03,0x06,0x05,0x0C,0x0B,0x1A,0x17,0x17,0x1D,0x37,0x2C,0x2F,0x3A,0x2F,0x3A,
//91: girl SW [6ad4f769-892d-44e3-83cd-ab4cf25a85be]
0x2F,0x3C,0x17,0x1B,0x33,0x2C,0x74,0x4F,0x78,0x5F,0x23,0x3F,0x17,0x1C,0x3F,0x3F,
//92: girl NE [382800f5-845e-4b8f-8d27-1063634818f7]
0xC0,0xC0,0x20,0xE0,0x10,0xF0,0x08,0xF8,0x48,0xF8,0xA4,0xFC,0xF4,0x5C,0xF4,0x5C,
//93: girl SE [f3b35159-3e03-4cc2-bd23-aac036517b72]
0xF4,0x3C,0xF8,0xD8,0xFC,0x24,0x3C,0xE4,0x18,0xF8,0x04,0xFC,0x88,0xF8,0xFC,0xFC,
//94: dwarf NW [d6e715ee-b5df-4df7-8a5a-68eb2c509ae1]
0x13,0x13,0x3D,0x2F,0x79,0x5F,0x7F,0x47,0x3F,0x28,0x1F,0x17,0x3F,0x2D,0x1F,0x1D,
//95: dwarf SW [c3489f80-be3b-48dd-ad51-7ae8e014f7aa]
0x6F,0x5B,0xE7,0x9C,0xF7,0x9E,0xF5,0xBF,0x5F,0x5B,0x10,0x1F,0x08,0x0F,0x3F,0x3F,
//96: dwarf NE [5841a414-bd44-440b-81c2-6bca6e214348]
0xC8,0x48,0xBC,0x74,0x9E,0x7A,0xFE,0x72,0xFC,0x14,0xF8,0xE8,0xFC,0xB4,0xF8,0xB8,
//97: dwarf SE [86a45564-c086-41a8-a7bf-834523f6a454]
0xF4,0xDC,0xEC,0x3C,0xDE,0x72,0x9E,0xF2,0xFC,0xFC,0x90,0xF0,0xE0,0xE0,0xFC,0xFC,
//98: crane NW [b9e82ba9-00a1-480f-ade4-6716c9586aa7]
0x00,0x00,0x03,0x03,0x0D,0x0E,0x17,0x18,0x2E,0x31,0x26,0x3F,0x6E,0x5F,0x7E,0x5F,
//99: crane SW [09888211-a01e-44b8-8a4f-fcd90a63307a]
0x7E,0x5F,0x5D,0x6E,0x2F,0x31,0x17,0x1B,0x0D,0x0A,0x0F,0x0A,0x07,0x0F,0x00,0x00,
//100: crane NE [ab9bf688-f938-4762-97e1-efa64d30b52b]
0x00,0x00,0x80,0x80,0x60,0xE0,0xD0,0x30,0xE8,0x18,0xC8,0xF8,0xEC,0xF4,0xFC,0xF4,
//101: crane SE [b23c9e34-2089-4edf-bd16-0eac2bba1af6]
0xFC,0xF4,0x74,0xEC,0xE8,0x18,0xD0,0xB0,0x60,0xA0,0xE0,0xA0,0xC0,0xE0,0x00,0x00,
//102: fire NW [ed0f7472-8830-4a44-87cd-de0bb2631c2a]
0x10,0x10,0x1F,0x1F,0x10,0x1F,0x48,0x4F,0x6B,0x6C,0x5B,0x7C,0x23,0x3E,0x13,0x1D,
//103: fire SW [e34d77c9-aa0c-4541-8aad-75591c671218]
0xEB,0xED,0x57,0x79,0x43,0x7C,0x27,0x38,0x27,0x38,0x13,0x1C,0x0E,0x0F,0x01,0x01,
//104: fire NE [74f73e82-b735-4d93-b2e3-637a284a0588]
0x00,0x00,0x83,0x83,0x4E,0xCE,0x32,0xFE,0x54,0xBC,0xC4,0x3C,0xF2,0x2E,0xF1,0x4F,
//105: fire SE [8eb467b2-e90a-4c97-8b8d-4b6db8e82fcf]
0xF9,0x47,0xFA,0x46,0xF2,0x0E,0xF5,0x8F,0xF2,0x8E,0xE4,0x9C,0x78,0x98,0xE0,0xE0,
//106: snowman NW [dcfa0df7-3532-4e81-b015-e404b8e2ed08]
0x01,0x01,0x03,0x02,0x0F,0x0C,0x0B,0x0F,0x04,0x07,0x3A,0x3F,0x7F,0x51,0x7F,0x60,
//107: snowman SW [7916d90e-627d-4c5c-8aea-e09c366c06ed]
0x7F,0x42,0x7F,0x40,0x7F,0x44,0x5F,0x60,0x3F,0x24,0x2F,0x30,0x18,0x1F,0x7F,0x7F,
//108: snowman NE [c885f293-c5b6-415b-a22d-6354cbd1c1a2]
0xF0,0xF0,0xF8,0x08,0xFC,0x84,0xFE,0x22,0xFE,0x82,0xFA,0x86,0xD2,0x2E,0xEC,0x1C,
//109: snowman SE [c7a11c10-6a25-48dc-80a4-dd4208f099ec]
0xF6,0x0E,0xFF,0x09,0xFF,0x09,0xF6,0x0E,0xE4,0x1C,0xC8,0x38,0x30,0xF0,0xFC,0xFC,
//110: bigtile NW [5631574f-7009-4403-97b1-d770566182fd]
0xFC,0x01,0xF8,0x03,0xF0,0x07,0xE0,0x0F,0xC0,0x1F,0x80,0x3F,0x00,0x7F,0x00,0xFF,
//111: bigtile SW [bcce002d-1409-47a4-a406-faa7d3a243f8]
0x00,0xFF,0x00,0x7F,0x80,0x3F,0xC0,0x1F,0xE0,0x0F,0xF0,0x07,0xF8,0x03,0xFC,0x01,
//112: bigtile NE [92780444-249f-439c-83c5-c8214e5fbb30]
0x3F,0x80,0x1F,0xC0,0x0F,0xE0,0x07,0xF0,0x03,0xF8,0x01,0xFC,0x00,0xFE,0x00,0xFF,
//113: bigtile SE [05a6ad35-fa56-46c0-a73b-e778774215b8]
0x00,0xFF,0x00,0xFE,0x01,0xFC,0x03,0xF8,0x07,0xF0,0x0F,0xE0,0x1F,0xC0,0x3F,0x80,
//114: ground1 NW [3b6ba972-84a4-4f73-8ff8-326464234589]
0x06,0x00,0x28,0x01,0x0C,0x03,0x00,0x00,0x20,0x00,0x02,0x00,0x60,0x00,0xB1,0x00,
//115: ground1 SW [eb0440ad-b560-4d02-a51c-a8a115237e3b]
0xE1,0x10,0x11,0x60,0x00,0x00,0x0C,0x00,0x56,0x00,0x0C,0x12,0x12,0x0C,0x00,0x00,
//116: ground1 NE [b755adb2-8714-44d4-95b0-736d0de2c5f1]
0x20,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x20,0x08,0x28,0x10,0x00,0x00,0x80,0x00,
//117: ground1 SE [04b469f7-692f-4623-8a6f-e5d3af98a406]
0x42,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x2C,0x00,0x38,0x04,0x04,0x18,
//118: remains NW [bb3d3c9d-398f-4d8a-938f-d13043cb9941]
0x00,0x00,0x00,0x18,0x00,0x25,0x10,0x49,0x20,0x50,0x00,0x6F,0x00,0x10,0x00,0x2C,
//119: remains SW [d2761097-0485-4bbd-8125-138b10b35cc2]
0x00,0x29,0x00,0x21,0x01,0x28,0x02,0x41,0x04,0x53,0x00,0x76,0x00,0x1D,0x00,0x01,
//120: remains NE [d1e183e9-67b6-452b-b47e-2a816f0eafea]
0x00,0x7C,0x00,0x82,0x82,0x3D,0x00,0xC3,0x00,0x00,0x00,0x06,0x00,0xC9,0x00,0x2B,
//121: remains SE [9f0eb30a-50b5-4565-acad-4db0b6b628ec]
0x00,0xAA,0x44,0xAA,0xC4,0x2A,0x00,0xCA,0x00,0x12,0x00,0xDA,0x40,0x2E,0x00,0xC0,
//122: snake NW [cfd60e8e-409d-4bc9-86a8-a27e5a9955f8]
0x07,0x07,0x08,0x0F,0x08,0x0F,0x12,0x1F,0x10,0x1F,0x24,0x3F,0x27,0x3B,0x27,0x39,
//123: snake SW [e008ee4c-3089-4664-8021-89867ff5fe46]
0x12,0x1F,0x37,0x38,0x48,0x7F,0x47,0x7C,0x3C,0x27,0x1F,0x1C,0x03,0x02,0x01,0x01,
//124: snake NE [26302e15-a8df-49eb-91a9-575fb5f50f8a]
0xC0,0xC0,0x20,0xE0,0x20,0xE0,0x90,0xF0,0x10,0xF0,0x4A,0xFA,0xCB,0xBB,0xCD,0x3F,
//125: snake SE [bc70f0c2-741f-4ff8-b41c-431c92c05b19]
0x11,0xFF,0xD6,0x3E,0x28,0xF8,0xC4,0x7C,0x44,0xFC,0xAC,0x74,0x58,0xA8,0xF0,0xF0,
//126: hero NW [ff311be6-cda1-47e5-a1f7-8e933e3afede]
0x07,0x07,0x0F,0x0F,0x0F,0x0F,0x1F,0x1B,0x1F,0x1B,0x09,0x0F,0x0F,0x0E,0x7F,0x7A,
//127: hero SW [a19a47f4-016a-42a3-b09f-a22c6203473e]
0x87,0xFC,0x6B,0x7F,0xF1,0x9F,0xFC,0x9F,0x6B,0x6F,0x08,0x0F,0x04,0x07,0x0F,0x0F,
//128: hero NE [c3cc8b02-9285-44c7-b0f7-fc920fe87d53]
0xE0,0xE0,0xF8,0xF8,0xFC,0xFC,0xF8,0xF8,0xFC,0x7C,0x38,0xF8,0xF0,0xF0,0xFE,0x5E,
//129: hero SE [4e19bfa5-aaf1-4b28-ac32-171b5f16a354]
0xFF,0x3F,0xF9,0xE7,0xBD,0xEF,0x3D,0xEF,0xFD,0xEF,0x9A,0xF6,0xEC,0xEC,0xF0,0xF0,
//130: hero2 NW [82db7cfa-4754-4ca4-8185-9f2829c188a6]
0x07,0x07,0x0F,0x0F,0x0F,0x0F,0x1F,0x1B,0x1F,0x1B,0x09,0x0F,0x0F,0x0E,0x7F,0x7A,
//131: hero2 SW [d5238e77-6ef4-468f-9f2d-3b7742ccd873]
0x87,0xFC,0x6B,0x7F,0x79,0x4F,0x6C,0x57,0x3F,0x27,0x19,0x1F,0x07,0x07,0x0F,0x0F,
//132: hero2 NE [8906265c-1776-4c39-bd48-1bc89c1afeac]
0xE0,0xE0,0xF8,0xF8,0xFC,0xFC,0xF8,0xF8,0xFC,0x7C,0x38,0xF8,0xF0,0xF0,0xFE,0x5E,
//133: hero2 SE [4b08c6f0-eaf6-4434-a8fc-83f983e89946]
0xFF,0x3F,0xF9,0xE7,0xBD,0xEF,0x3D,0xEF,0xFD,0xEF,0x1A,0xF6,0x3C,0xFC,0xF0,0xF0,
//134: Hero up NW [7ce3d81a-6e60-43f6-b362-fe87e93c0968]
0x07,0x07,0x1F,0x1F,0x3F,0x3F,0x1F,0x1F,0x3F,0x3F,0x1F,0x1F,0x0F,0x0F,0x7F,0x7B,
//135: Hero up SW [59462c01-3528-4432-bcd1-ed02ac8a993f]
0x87,0xFC,0xEB,0xFF,0xF8,0xDF,0xFC,0xDF,0xAB,0xFF,0x48,0x7F,0x3C,0x3F,0x0F,0x0F,
//136: Hero up NE [1c6af64d-b00c-4553-8526-4471eab9f467]
0xE0,0xE0,0xB0,0xF0,0xD0,0xF0,0xF8,0xF8,0xF8,0xF8,0xF0,0xF0,0xF0,0xF0,0xFE,0xDE,
//137: Hero up SE [af108836-40bc-49b4-bd7b-627632deaefd]
0xE1,0x3F,0xD6,0xFE,0x1E,0xFA,0x3E,0xF2,0xFC,0xF4,0x98,0xF8,0xE0,0xE0,0xF0,0xF0,
//138: Hero up 2 NW [2c8e0477-7778-42a9-aba3-d4079b775996]
0x07,0x07,0x1F,0x1F,0x3F,0x3F,0x1F,0x1F,0x3F,0x3F,0x1F,0x1F,0x0F,0x0F,0x7F,0x7B,
//139: Hero up 2 SW [9b48acf1-5995-43dd-95b6-f3b77005a95d]
0x87,0xFC,0xEB,0xFF,0xF8,0xDF,0xFC,0xDF,0xAF,0xFF,0x49,0x7F,0x3F,0x3F,0x0F,0x0F,
//140: Hero up 2 NE [ab952990-ebe4-4a88-ac4c-008171898d39]
0xE0,0xE0,0xB0,0xF0,0xD0,0xF0,0xF8,0xF8,0xF8,0xF8,0xF0,0xF0,0xF0,0xF0,0xFE,0xDE,
//141: Hero up 2 SE [d28cb003-7d32-4cc0-b97a-fe31518a2da2]
0xE1,0x3F,0xD6,0xFE,0x1C,0xFC,0x3C,0xF4,0xD8,0xF8,0x10,0xF0,0x20,0xE0,0xF0,0xF0,
//142: Hero left NW [4519b296-e55e-49c1-837b-f1dcb3c1716a]
0x07,0x07,0x1F,0x1F,0x1F,0x1F,0x1F,0x1B,0x1B,0x1F,0x6F,0x69,0xAF,0xEE,0xAF,0xEA,
//143: Hero left SW [fb367f64-2921-409c-a380-92ee12fb2bc8]
0xBF,0xF8,0xBF,0xEF,0xBC,0xEF,0xB9,0xFF,0xAF,0xEF,0x62,0x63,0x04,0x07,0x07,0x07,
//144: Hero left NE [d160ac5c-a0f0-46b1-b950-2972f581a9fc]
0xE0,0xE0,0xF8,0xF8,0xFC,0xFC,0x78,0xF8,0xBE,0xFE,0xFC,0xFC,0xF8,0xB8,0xF0,0x30,
//145: Hero left SE [33f3441e-7600-4f04-8c3d-ed3608226812]
0xF8,0xF8,0x44,0xFC,0xF8,0x98,0xF8,0x18,0xE8,0x38,0xF0,0xF0,0x20,0xE0,0xE0,0xE0,
//146: Hero left 2 NW [ad8cd824-49c2-4ed9-90d9-41cd43c3d906]
0x00,0x00,0x0F,0x0F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1B,0x0B,0x0F,0x6F,0x69,0xAF,0xEE,
//147: Hero left 2 SW [99a103c1-b771-4fab-955f-0194f29e5934]
0xAF,0xEA,0xBF,0xF8,0xBF,0xEF,0xB8,0xEF,0xBD,0xFF,0xA3,0xFF,0x73,0x7F,0x1F,0x1F,
//148: Hero left 2 NE [faba39bc-b008-4191-b5c2-5f9e7c37beb0]
0x00,0x00,0xE0,0xE0,0xF8,0xF8,0xFC,0xFC,0x78,0xF8,0xBC,0xFC,0xFE,0xFE,0xFC,0xBC,
//149: Hero left 2 SE [49cfe64c-f277-4562-a685-c5395a390c7d]
0xF0,0x30,0xF8,0xF8,0x84,0xFC,0xF8,0xC8,0xFC,0xC4,0x3C,0xE4,0xDC,0xFC,0xFE,0xFE,
//150: Window 1 [fac61afa-9fea-4a7d-b19c-7ee95b59d3b5]
0x1F,0x1F,0x3F,0x20,0x70,0x40,0xE0,0x87,0xC3,0x8F,0xC4,0x9C,0xC8,0x98,0xC8,0x98,
//151: Window 2 [77999184-53d6-4644-9f0e-0ba71b52313e]
0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
//152: Window 3 [9de94ebe-1b97-4b2a-97b3-5e79292c1599]
0xF8,0xF8,0xFC,0x04,0x0E,0x02,0x07,0xE1,0xC3,0xF1,0x39,0x23,0x09,0x13,0x09,0x13,
//153: Window 4 [0e00f8d2-adc8-4f52-b287-6aa0b8c364f8]
0xC8,0x98,0xC8,0x98,0xC8,0x98,0xC8,0x98,0xC8,0x98,0xC8,0x98,0xC8,0x98,0xC8,0x98,
//154: Window 5 [fb47fabb-0a97-439d-8833-ac5eb718a964]
0x09,0x13,0x09,0x13,0x09,0x13,0x09,0x13,0x09,0x13,0x09,0x13,0x09,0x13,0x09,0x13,
//155: Window 6 [36541604-9827-4633-8f2a-f23aaf0a081e]
0xC8,0x98,0xC8,0x98,0xC8,0x94,0xCC,0x83,0xE7,0x80,0x70,0x40,0x30,0x2F,0x1F,0x1F,
//156: Window 7 [580cc511-2ebd-4fe9-ae33-32fb31dfc1e7]
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,
//157: Window 8 [cf7a8011-acf9-4c1d-9d10-ea53c4a7b46e]
0x09,0x13,0x09,0x13,0x19,0x23,0x31,0xC3,0xE1,0x07,0x02,0x0E,0x04,0xFC,0xF8,0xF8,
//158: Letter 1 [e2280cef-8777-4ce8-bd4d-067c4948bf96]
0x1C,0x1C,0x36,0x36,0x22,0x22,0x63,0x63,0x7F,0x7F,0x63,0x63,0x63,0x63,0x00,0x00,
//159: Letter 2 [724d4246-41b7-498b-a078-04d360eaf021]
0x7E,0x7E,0x63,0x63,0x63,0x63,0x7E,0x7E,0x63,0x63,0x63,0x63,0x7E,0x7E,0x00,0x00,
//160: Letter 3 [56774d73-1163-4759-b448-1333cf2c0071]
0x1E,0x1E,0x33,0x33,0x60,0x60,0x60,0x60,0x60,0x60,0x33,0x33,0x1E,0x1E,0x00,0x00,
//161: Letter 4 [034a6789-64c7-46a3-8a9e-c0340cd3c7fb]
0x7C,0x7C,0x66,0x66,0x63,0x63,0x63,0x63,0x63,0x63,0x66,0x66,0x7C,0x7C,0x00,0x00,
//162: Letter 5 [82963de3-38a1-4107-af16-0d39e46a18b7]
0x7F,0x7F,0x60,0x60,0x60,0x60,0x7E,0x7E,0x60,0x60,0x60,0x60,0x7F,0x7F,0x00,0x00,
//163: Letter 6 [5b98b850-5596-4213-816e-e7345c34d17c]
0x7F,0x7F,0x60,0x60,0x60,0x60,0x7E,0x7E,0x60,0x60,0x60,0x60,0x60,0x60,0x00,0x00,
//164: Letter 7 [c674ac9b-9f42-4730-a8e3-0e404b171fb9]
0x3E,0x3E,0x63,0x63,0x60,0x60,0x6F,0x6F,0x63,0x63,0x63,0x63,0x3E,0x3E,0x00,0x00,
//165: Letter 8 [10628311-138c-4f45-b69d-3f1d178f88ef]
0x63,0x63,0x63,0x63,0x63,0x63,0x7F,0x7F,0x63,0x63,0x63,0x63,0x63,0x63,0x00,0x00,
//166: Letter 9 [8bec05fa-2550-421f-9bc6-62104368b5d9]
0x3F,0x3F,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3F,0x3F,0x00,0x00,
//167: Letter 10 [23af0421-41e2-47aa-b111-29433cbe2223]
0x3F,0x3F,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x46,0x46,0x3C,0x3C,0x00,0x00,
//168: Letter 11 [b24058ea-28f9-4a96-b378-525b06e1aa40]
0x63,0x63,0x66,0x66,0x6C,0x6C,0x78,0x78,0x6C,0x6C,0x66,0x66,0x63,0x63,0x00,0x00,
//169: Letter 12 [7aedf32e-4882-4a57-886a-0e40f67dffe3]
0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x7F,0x7F,0x00,0x00,
//170: Letter 13 [142a0d84-ed59-4331-b633-930af13edf7e]
0x41,0x41,0x63,0x63,0x77,0x77,0x7F,0x7F,0x6B,0x6B,0x63,0x63,0x63,0x63,0x00,0x00,
//171: Letter 14 [79c6831e-a709-41b3-9972-b8594bf0cbb1]
0x63,0x63,0x73,0x73,0x7B,0x7B,0x6F,0x6F,0x67,0x67,0x63,0x63,0x61,0x61,0x00,0x00,
//172: Letter 15 [6c0e948f-a604-4a06-9291-0d69d4a3a526]
0x3E,0x3E,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x3E,0x3E,0x00,0x00,
//173: Letter 16 [48b30a5a-206a-48a4-8492-65ed681f6377]
0x7E,0x7E,0x63,0x63,0x63,0x63,0x63,0x63,0x7E,0x7E,0x60,0x60,0x60,0x60,0x00,0x00,
//174: Letter 17 [a582df11-9149-4993-8122-ffdabab1d5ed]
0x3E,0x3E,0x63,0x63,0x63,0x63,0x63,0x63,0x6B,0x6B,0x67,0x67,0x3E,0x3E,0x01,0x01,
//175: Letter 18 [d40c9b09-810f-4ff8-97a8-c6f1de84e615]
0x7E,0x7E,0x63,0x63,0x63,0x63,0x67,0x67,0x7C,0x7C,0x6E,0x6E,0x67,0x67,0x00,0x00,
//176: Letter 19 [d1bb8ab9-dc06-45df-a764-f97ccac62a75]
0x3E,0x3E,0x63,0x63,0x60,0x60,0x3E,0x3E,0x03,0x03,0x63,0x63,0x3E,0x3E,0x00,0x00,
//177: Letter 20 [413d0ec2-7ded-4a73-b159-3afc599678cb]
0xFF,0xFF,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00,
//178: Letter 21 [e0b359cb-799f-4615-9235-59b88dde3b23]
0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x3E,0x3E,0x00,0x00,
//179: Letter 22 [be2e151b-ddd9-4e7f-878f-afa00f888478]
0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x36,0x36,0x36,0x36,0x1C,0x1C,0x00,0x00,
//180: Letter 23 [26277483-32ce-4505-bc7f-067482dc4c28]
0x63,0x63,0x63,0x63,0x6B,0x6B,0x6B,0x6B,0x7F,0x7F,0x77,0x77,0x22,0x22,0x00,0x00,
//181: Letter 24 [ffffd358-3d88-4cc5-bdca-f926a16fcc95]
0x63,0x63,0x63,0x63,0x36,0x36,0x1C,0x1C,0x36,0x36,0x63,0x63,0x63,0x63,0x00,0x00,
//182: Letter 25 [ec782b0a-938b-4486-9889-6f43cf002f3f]
0x33,0x33,0x33,0x33,0x33,0x33,0x1E,0x1E,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x00,0x00,
//183: Letter 26 [8061da18-8f53-4976-b1a9-ccfa96a555e4]
0x7F,0x7F,0x03,0x03,0x06,0x06,0x18,0x18,0x30,0x30,0x60,0x60,0x7F,0x7F,0x00,0x00,
//184: Letter comma [ac36c7fd-6767-4c8f-807c-dd33522fcc3c]
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x18,0x18,0x10,0x10,
//185: Letter dot [585a4a76-8de0-4d60-8983-70e390f5d0ef]
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x30,0x30,0x00,0x00,
//186: Letter excl [7db8fa89-8bbc-4a28-8991-541da97ee7e1]
0x08,0x08,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x08,0x08,0x08,0x08,0x00,0x00,0x08,0x08,
//187: Letter question [4a424ff6-1cfa-47de-8349-3755d310b699]
0x3C,0x3C,0x66,0x66,0x66,0x66,0x0C,0x0C,0x18,0x18,0x18,0x18,0x00,0x00,0x18,0x18,
//188: cle [5546d72f-315a-4e8d-ab19-e7d9ba380d7c]
0x00,0x70,0x70,0xF8,0xD0,0xD8,0xF3,0xFB,0x7A,0x7F,0x0C,0x0E,0x06,0x07,0x03,0x03,
//189: potion [58ce8f2e-7a53-447d-820f-c38a95498871]
0x02,0x3E,0x06,0x22,0x04,0x14,0x06,0x22,0x1F,0x5D,0x1F,0x5D,0x0E,0x22,0x04,0x1C,
//190: bonbon [8dbb1bcc-df5b-4fd0-b3d4-73adadbcb150]
0x06,0x06,0x3D,0x3B,0x57,0x67,0x5E,0x42,0x76,0x42,0xFA,0xE6,0xBC,0xDC,0x60,0x60,
//191: bourse [dec644cc-83a8-4629-aa67-a59c8c1bceb1]
0x06,0x06,0x0A,0x0A,0x3D,0x39,0x47,0x47,0x82,0x82,0xC6,0x82,0xBA,0xC6,0x7C,0x7C,
//192: Number 1 [6c0e948f-a604-4a06-9291-0d69d4a3a526]
0x3E,0x3E,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x3E,0x3E,0x00,0x00,
//193: Number 2 [e9cb6c7e-fb97-4771-8b9b-26e47d4096e0]
0x18,0x18,0x38,0x38,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x3C,0x3C,0x00,0x00,
//194: Number 3 [ee6feac0-abee-4269-be78-997deb29813c]
0x3E,0x3E,0x63,0x63,0x63,0x63,0x06,0x06,0x18,0x18,0x30,0x30,0x7F,0x7F,0x00,0x00,
//195: Number 4 [052d6d8d-4ef8-4e22-8195-8fff2ecf937f]
0x3E,0x3E,0x63,0x63,0x63,0x63,0x0E,0x0E,0x63,0x63,0x63,0x63,0x3E,0x3E,0x00,0x00,
//196: Number 5 [5a4eb57c-bc99-4908-9e09-908a8bec5872]
0x0E,0x0E,0x1E,0x1E,0x36,0x36,0x26,0x26,0x66,0x66,0x7F,0x7F,0x06,0x06,0x00,0x00,
//197: Number 6 [c7f8f31d-832c-45d9-9cd8-863fe268c8d0]
0x7F,0x7F,0x60,0x60,0x7E,0x7E,0x03,0x03,0x03,0x03,0x63,0x63,0x3E,0x3E,0x00,0x00,
//198: Number 7 [fae4e7de-c86a-4c7c-8f4b-40b65689594d]
0x3E,0x3E,0x63,0x63,0x60,0x60,0x7E,0x7E,0x63,0x63,0x63,0x63,0x3E,0x3E,0x00,0x00,
//199: Number 8 [88d02011-5de8-4f7c-be88-7c4d199f9373]
0x7F,0x7F,0x63,0x63,0x63,0x63,0x06,0x06,0x0C,0x0C,0x18,0x18,0x18,0x18,0x00,0x00,
//200: Number 9 [540869f9-5fb9-445d-931b-50f477f11e4a]
0x3E,0x3E,0x63,0x63,0x63,0x63,0x3E,0x3E,0x63,0x63,0x63,0x63,0x3E,0x3E,0x00,0x00,
//201: Number 10 [23a8f6fa-620e-4c99-8045-461525b4e825]
0x3E,0x3E,0x63,0x63,0x63,0x63,0x3F,0x3F,0x03,0x03,0x63,0x63,0x3E,0x3E,0x00,0x00,
//202: heart 0 [d6171f59-1398-45bb-ae93-8c6f8e1d9e7a]
0x00,0x00,0x6C,0x00,0x92,0x00,0x82,0x00,0x82,0x00,0x44,0x00,0x28,0x00,0x10,0x00,
//203: heart half [fe38cb26-38fe-4072-9553-a0147ff6ea9d]
0x00,0x00,0x6C,0x60,0xF2,0x90,0xC2,0xB0,0x82,0xF0,0x44,0x70,0x28,0x30,0x10,0x10,
//204: heart full [8f502134-b288-4b75-a296-84e1c94b244c]
0x00,0x00,0x6C,0x6C,0xFE,0x92,0xD6,0xAA,0xC6,0xBA,0x6C,0x54,0x38,0x28,0x10,0x10,
//205: epee [917a6dbc-29d3-4434-8daf-52561ef2ea1b]
0x00,0xC0,0x80,0xA0,0x41,0x51,0x23,0x2B,0x16,0x16,0x0E,0x0E,0x1F,0x1F,0x33,0x33,
//206: hache [ad68970e-d6bb-44cf-853f-d4819fd77546]
0x0C,0x0C,0x3C,0x3C,0x7C,0x78,0x38,0xBC,0x14,0x56,0x02,0x23,0x01,0x01,0x00,0x00,
//207: bouclier [0e91cb88-5773-48ec-970e-bb1de68283b7]
0xFF,0xFF,0x8F,0x81,0xB3,0x8D,0xAB,0x9D,0xAB,0x9D,0x56,0x4A,0x2C,0x24,0x18,0x18,
//208: chaise NW [6f99c213-07c0-45fd-948e-0289e0d5113c]
0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x07,0x08,0x08,0x10,0x10,0x10,0x10,0x1E,0x10,
//209: chaise SW [0145cd61-e6fa-4153-8009-4b90d0c71074]
0x10,0x10,0x11,0x10,0x18,0x18,0x1F,0x17,0x1F,0x18,0x1F,0x17,0x1F,0x17,0x0F,0x0F,
//210: chaise NE [6b85f6eb-0486-42ee-a58a-3e9a05bb0ded]
0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xE0,0x10,0x10,0x78,0x08,0x08,0x08,0x88,0x08,
//211: chaise SE [4f914889-fb4f-4bad-8256-6be5b4e6dbef]
0x08,0x08,0xF8,0x08,0x18,0x18,0xF8,0xE8,0xF8,0x18,0xF8,0xE8,0xF8,0xE8,0xF0,0xF0,
//212: fireball NW [da94b153-c7c5-4ca2-9faa-d395bfc69011]
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x0F,0x0F,0x06,0x07,
//213: fireball SW [9c3e057a-8eec-4f86-8745-ce83982794c5]
0x0D,0x0E,0x06,0x07,0x07,0x07,0x05,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//214: fireball NE [dab4c0e0-4be7-43c6-8811-069b3ea58151]
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xA0,0xA0,0x60,0xE0,0xF0,0x70,
//215: fireball SE [4ff1670a-c577-4da0-bbad-906dff5eb4bc]
0xA0,0x60,0x30,0xF0,0x40,0xC0,0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//216: swordman NW [25eb11a9-616a-4253-bf80-3eb0e9a7ea97]
0x07,0x07,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x1F,0x1E,0x5F,0x5E,0xFF,0xBA,0xF7,0x8C,
//217: swordman SW [fa560941-68a6-473c-b12e-a79718654567]
0x6B,0x5F,0xB4,0xFB,0xD9,0xBF,0xFF,0xBE,0xF8,0xFF,0xBB,0xFF,0xAC,0xEF,0x4C,0x4F,
//218: swordman NE [c8f97292-322b-4481-a6ab-3425f252478d]
0xE0,0xE0,0xF0,0xF0,0xF0,0xB0,0x30,0xF0,0xF0,0x30,0xF2,0xF2,0xFF,0x5D,0xEF,0x31,
//219: swordman SE [e7b6e9a2-64e0-4790-82fc-b49f12cadeb9]
0xD7,0xFF,0x2F,0xD9,0x9F,0xF9,0xFF,0x7F,0x9F,0xFF,0xDD,0xFF,0xB5,0xF7,0xFA,0xFA,
//220: hatman NW [48c83b93-1dcf-472d-bf6f-d5cd385f170f]
0x03,0x03,0x7D,0x7F,0x8C,0xFB,0x47,0x7C,0x23,0x3F,0x18,0x1F,0x2F,0x37,0x3F,0x2A,
//221: hatman SW [e4deacfb-55de-4c5f-8299-4e5ef64397f9]
0x5F,0x7A,0xBF,0xE4,0xBF,0xE7,0xBE,0xFF,0xB9,0xFF,0xBD,0xFF,0xA7,0xE7,0x4F,0x4F,
//222: hatman NE [36e3e82e-733b-4b48-8da1-98f7f3e3c8ed]
0xD8,0xD8,0x3E,0xE6,0xB9,0xEF,0xF2,0x1E,0xE4,0xFC,0x18,0xF8,0xF4,0xEC,0xFC,0x54,
//223: hatman SE [3dc66296-7db4-4b67-9a6a-c617fed22a4d]
0xFA,0x5E,0xED,0x3F,0xDF,0xF3,0x3F,0xF3,0xFD,0xDF,0x1D,0xFF,0x25,0xE7,0xFA,0xFA,
//224: warg NW [cf51800c-225b-41c0-ba94-d2b712d97e50]
0x1A,0x1A,0x25,0x3F,0x30,0x3F,0x40,0x7F,0xAE,0xFF,0x47,0x7D,0x50,0x7F,0x3B,0x3D,
//225: warg SW [a2d15b0d-8cb3-40fc-803e-087806e5a58c]
0x4C,0x77,0x9F,0xE3,0xAF,0xF0,0x70,0x7F,0x1F,0x10,0x10,0x1F,0x0D,0x0A,0x1F,0x1F,
//226: warg NE [642cb6e5-e52e-4cf2-9e40-6769d1a8b460]
0xD8,0xD8,0x24,0xFC,0x0C,0xFC,0x02,0xFE,0x75,0xFF,0xE2,0xBE,0x0A,0xFE,0xDC,0xBC,
//227: warg SE [c7059c7f-c699-4215-96d9-6d31c6d6b411]
0x24,0xFC,0xF2,0xCE,0xF1,0x0F,0x09,0xFF,0xE9,0x1F,0x96,0xF6,0xF0,0xF0,0xFC,0xFC,
//228: champiguy NW [560d87bb-3e92-4ad9-b5b1-d7beae42ce95]
0x03,0x03,0x0C,0x0F,0x10,0x1F,0x20,0x3F,0x47,0x7F,0x9F,0xF8,0xBF,0xE4,0xBF,0xF4,
//229: champiguy SW [71a6ca39-8e11-4824-bef1-4700df739c10]
0x7F,0x74,0xFC,0x93,0xFC,0xA3,0x7F,0x60,0x1F,0x10,0x0F,0x0F,0x1F,0x10,0x1F,0x1F,
//230: champiguy NE [c47f5084-e4fc-4479-9c86-557a906e4a6a]
0x80,0x80,0x60,0xE0,0x10,0xF0,0x08,0xF8,0xE4,0xFC,0xF2,0x1E,0xFA,0x9E,0xFC,0x8C,
//231: champiguy SE [e450a4eb-fc7c-4820-a64c-ab4b6deff980]
0xFE,0x92,0xFE,0x32,0xFC,0x4C,0xFC,0x44,0xFC,0x44,0xFC,0xE4,0xB8,0xB8,0x80,0x80,
//232: patamodeler NW [5e92e395-24a6-4f0f-8cb7-5564bbd3e393]
0x38,0x38,0x45,0x7D,0xAB,0xFF,0xAF,0xFF,0xF8,0xF8,0x48,0x78,0x47,0x7F,0x4B,0x7C,
//233: patamodeler SW [f206ce4a-2c8e-4247-98f4-c6efb43d8788]
0x45,0x7F,0x55,0x7F,0x75,0x7F,0x28,0x3F,0x2A,0x3F,0x2F,0x3F,0x28,0x3F,0x40,0x7A,
//234: patamodeler NE [73786cb0-7d99-4bd3-a3ac-165b95e410f4]
0xF8,0xF8,0x1C,0xE4,0x56,0xFA,0xD2,0xFE,0x3A,0x3E,0x21,0x3F,0x91,0x9F,0xD1,0x5F,
//235: patamodeler SE [26524351-37a3-42eb-adf9-6ca2af9fc362]
0x61,0xBF,0x05,0xFF,0x0D,0xFF,0x4A,0xFA,0xC8,0xF8,0xC4,0xFC,0x44,0xEC,0x03,0xD7,
//236: momie NW [75b5b5af-e80a-4fde-bb7c-8199ffd34afe]
0x01,0x01,0x03,0x02,0x07,0x04,0x07,0x07,0x07,0x06,0x77,0x76,0xFF,0x8D,0xF5,0xAE,
//237: momie SW [248416f2-65cb-498f-a19d-c30267a5c066]
0xFE,0xAB,0x79,0x7F,0x3F,0x28,0x38,0x2F,0x77,0x55,0xE7,0xA7,0xCF,0xCE,0x03,0x03,
//238: momie NE [2db731e9-6d4a-486d-8b92-86a776b4ffea]
0xE0,0xE0,0xB0,0x50,0x78,0x88,0xF8,0xE8,0xF8,0xB8,0xFC,0xBC,0xFE,0xE2,0xFD,0x2B,
//239: momie SE [8ad94b95-c48b-48f1-a8aa-a5f53540d847]
0x3F,0xEB,0xDF,0xFD,0xFE,0x0A,0x8E,0xFA,0xFE,0x0A,0x17,0xF5,0xF3,0x13,0xF8,0xF8,
//240: pumpkin NW [d99bfc76-c99e-45d8-9dfe-f14b0b471621]
0x00,0x00,0x00,0x00,0x03,0x03,0x1E,0x1F,0x77,0x6E,0xE3,0x9E,0xD7,0xAF,0xF0,0xAF,
//241: pumpkin SW [456afc50-3a71-41a1-9adf-b2c5510dad67]
0xE9,0xBF,0xDD,0xAF,0xE1,0xBF,0xF9,0xBF,0x51,0x7F,0x31,0x3F,0x0F,0x0F,0x00,0x00,
//242: pumpkin NE [714225da-ef09-4fa9-b93b-3a0a65788bce]
0x00,0x00,0x00,0x00,0x80,0x80,0xF0,0xF0,0xCC,0xFC,0x92,0xFE,0xCA,0xFE,0x4A,0xBE,
//243: pumpkin SE [9edb61d9-c7f1-4b9b-bb86-1ad884f98c00]
0x8A,0x7E,0x8A,0x7E,0x8A,0x7E,0x94,0x7C,0x94,0x7C,0x98,0x78,0xE0,0xE0,0x00,0x00,
//244: book [9dfccceb-9348-4f6e-b147-994a85bce45f]
0x7F,0x7F,0xFF,0x81,0xF3,0xB1,0xCF,0x8D,0xFF,0x81,0xFF,0xFF,0x80,0xFF,0x7F,0x7F,
//245: drink [27dfc8eb-a201-4b95-8b20-b51d42a9c2ab]
0x78,0x00,0xFF,0xFF,0xB5,0x8D,0xB5,0x8D,0xB5,0x8D,0xB5,0x8D,0x86,0xFE,0x7C,0x7C,
//246: tiled floor [26849038-da81-425f-b8ba-8658a9bca556]
0x10,0x00,0x20,0x00,0x40,0x00,0xA0,0x00,0x11,0x00,0x0A,0x00,0x04,0x00,0x08,0x00
};

