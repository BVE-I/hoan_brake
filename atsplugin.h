//=============================
// BVE ATS プラグイン ヘッダー ファイル
//
//             Rock_On, mackoy
//=============================

#ifdef ATS_EXPORTS
#define ATS_API __declspec(dllexport)
#else
#define ATS_API __declspec(dllimport)
#endif

// ATS プラグイン バージョン
#define ATS_VERSION	0x00020000

// ATS キー
#define ATS_KEY_S	0	// スペース Key
#define ATS_KEY_A1	1	// インサート Key
#define ATS_KEY_A2	2	// デリート Key
#define ATS_KEY_B1	3	// ホーム Key
#define ATS_KEY_B2	4	// エンド Key
#define ATS_KEY_C1	5	// ページアップ Key
#define ATS_KEY_C2	6	// ページダウン Key
#define ATS_KEY_D	7	// 2 Key
#define ATS_KEY_E	8	// 3 Key
#define ATS_KEY_F	9	// 4 Key
#define ATS_KEY_G	10	// 5 Key
#define ATS_KEY_H	11	// 6 Key
#define ATS_KEY_I	12	// 7 Key
#define ATS_KEY_J	13	// 8 Key
#define ATS_KEY_K	14	// 9 Key
#define ATS_KEY_L	15	// 0 Key

// ゲーム開始時のブレーキ弁の状態です。次のいずれかの値を返します。
#define ATS_INIT_REMOVED	2	// 常用位置
#define ATS_INIT_EMG		1	// 非常位置
#define ATS_INIT_SVC		0	// 	抜き取り (通常、保安装置未投入)

// サウンドコントロール指示
#define ATS_SOUND_STOP			-10000	// 停止
#define ATS_SOUND_PLAY			1		// 1 回再生
#define ATS_SOUND_PLAYLOOPING	0		// 繰り返し再生
#define ATS_SOUND_CONTINUE		2		// 現在の状態を維持する

// 警笛が扱われたときに呼び出される関数です。
#define ATS_HORN_PRIMARY	0	// 警笛1
#define ATS_HORN_SECONDARY	1	// 警笛2
#define ATS_HORN_MUSIC		2	// ミュージックホーン

// 定速制御の状態。
#define ATS_CONSTANTSPEED_CONTINUE	0	// 起動
#define ATS_CONSTANTSPEED_ENABLE	1	// 停止
#define ATS_CONSTANTSPEED_DISABLE	2	// 現在の状態を維持する

// 車両諸元
struct ATS_VEHICLESPEC
{
	int BrakeNotches;	// ブレーキノッチ数。
	int PowerNotches;	// 力行ノッチ数。
	int AtsNotch;		// ATS確認ノッチ。
	int B67Notch;		// ブレーキ弁 67 度に相当するノッチ。
	int Cars;			// 編成両数。
};

// 車両の状態量
struct ATS_VEHICLESTATE
{
	double Location;	// 列車位置 [m]。
	float Speed;		// 列車速度 [km/h]。
	int Time;			// 現在時刻 [ms]。
	float BcPressure;	// ブレーキシリンダ圧力 [kPa]。
	float MrPressure;	// 元空気ダメ圧力 [kPa]。
	float ErPressure;	// 釣り合い空気ダメ圧力 [kPa]。
	float BpPressure;	// ブレーキ管圧力 [kPa]。
	float SapPressure;	// 直通管圧力 [kPa]。
	float Current;		// 電流 [A]。
};

// 車上子で受け取った情報
struct ATS_BEACONDATA
{
	int Type;		// 地上子種別。
	int Signal;		// 対となるセクションの信号。
	float Distance;	// 対となるセクションまでの距離 [m]。
	int Optional;	// 地上子に設定された任意の値。
};

// Bve trainsim に渡すハンドル制御値
struct ATS_HANDLES
{
	int Brake;				// ブレーキノッチ。
	int Power;				// 力行ノッチ。
	int Reverser;			// レバーサー位置。
	int ConstantSpeed;		// 定速制御の状態。
};

// プラグインが読み込まれたときに呼び出される関数です。
ATS_API void WINAPI Load(void);

// プラグインが解放されたときに呼び出される関数です。
ATS_API void WINAPI Dispose(void);

// この ATS プラグインが準じているフォーマットを返す関数です。
ATS_API int WINAPI GetPluginVersion(void);

// 車両読み込み時に呼び出される関数です。
ATS_API void WINAPI SetVehicleSpec(ATS_VEHICLESPEC);

// ゲーム開始 ([開く] または [はじめから] 選択) 時に呼び出される関数です。
ATS_API void WINAPI Initialize(int);

// 1 フレームごとに呼び出される関数です。
ATS_API ATS_HANDLES WINAPI Elapse(ATS_VEHICLESTATE, int *, int *);

// 主ハンドルが扱われたときに呼び出される関数です。
ATS_API void WINAPI SetPower(int);

// ブレーキが扱われたときに呼び出される関数です。
ATS_API void WINAPI SetBrake(int);

// レバーサーが扱われたときに呼び出される関数です。
ATS_API void WINAPI SetReverser(int);

// ATS キーが押されたときに呼び出される関数です。
ATS_API void WINAPI KeyDown(int);

// ATS キーが離されたときに呼び出される関数です。
ATS_API void WINAPI KeyUp(int);

// 警笛が扱われたときに呼び出される関数です。
ATS_API void WINAPI HornBlow(int);

// 客室ドアが開いたときに呼び出される関数です。
ATS_API void WINAPI DoorOpen(void);

// 客室ドアが閉まったときに呼び出される関数です。
ATS_API void WINAPI DoorClose(void);

// 現在の閉そくの信号が変化したときに呼び出される関数です
ATS_API void WINAPI SetSignal(int);

// 地上子を越えたときに呼び出される関数です。
ATS_API void WINAPI SetBeaconData(ATS_BEACONDATA);

// このプラグインがBVEによって読み込まれた時に呼び出される。
ATS_API void WINAPI Load();

// このプラグインがBVEから解放された時に呼び出される。
ATS_API void WINAPI Dispose();