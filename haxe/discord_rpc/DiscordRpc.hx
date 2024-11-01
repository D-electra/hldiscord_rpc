package discord_rpc;

/** Detailed description in README.md **/
@:structInit
class DiscordRichPresence {
	public var state:hl.Bytes = null;
	public var details:hl.Bytes = null;
	public var startTimestamp = 0i64;
	public var endTimestamp = 0i64;
	public var largeImageKey:hl.Bytes = null;
	public var largeImageText:hl.Bytes = null;
	public var smallImageKey:hl.Bytes = null;
	public var smallImageText:hl.Bytes = null;
	public var partyId:hl.Bytes = null;
	public var partySize = 0;
	public var partyMax = 0;
	public var matchSecret:hl.Bytes = null;
	public var joinSecret:hl.Bytes = null;
	public var spectateSecret:hl.Bytes = null;
	public var instance:hl.UI8 = 0;
}

/** Discord connection event handlers **/
@:structInit
class DiscordEventHandlers {
	/** Called once Discord has connected and is ready to start **/
	public var ready:(userId:hl.Bytes, username:hl.Bytes, discriminator:hl.Bytes, avatar:hl.Bytes) -> Void = null;
	
	/** Called when discord has disconnected the program **/
	public var disconnected:(errorCode:Int, message:hl.Bytes) -> Void = null;

	/** Called when an error occurred **/
	public var errored:(errorCode:Int, message:hl.Bytes) -> Void = null;

	/** Called when the user has joined a game through Discord **/
	public var joinGame:(joinSecret:hl.Bytes) -> Void = null;

	/** Called when the user has spectated a game through Discord **/
	public var spectateGame:(spectateSecret:hl.Bytes) -> Void = null;

	/** Called when the user has recieved a join request **/
	public var joinRequest:(userId:hl.Bytes, username:hl.Bytes, discriminator:hl.Bytes, avatar:hl.Bytes) -> Void = null;
}

/** Wrapper of Discord-RPC library **/
class DiscordRpc {
	/** Attempts to connect to discord and initialize itself **/
	@:hlNative('discord_rpc', 'initialize')
	public static function initialize(applicationId:hl.Bytes, handlers:DiscordEventHandlers, autoRegister:Int, optionalSteamId:hl.Bytes):Void return;
	
	/** Stops activity from showing **/
	@:hlNative('discord_rpc', 'shutdown')
	public static function shutdown():Void return;
	
	/** Run any callbacks **/
	@:hlNative('discord_rpc', 'run_callbacks')
	public static function runCallbacks():Void return;

	/** Set activity for Discord **/
	@:hlNative('discord_rpc', 'update_presence')
	public static function updatePresence(presence:DiscordRichPresence):Void return;
	
	/** Clear activity **/
	@:hlNative('discord_rpc', 'clear_presence')
	public static function clearPresence():Void return;

	/** Respond to a join request **/
	@:hlNative('discord_rpc', 'respond')
	public static function respond(userid:hl.Bytes, reply:Int):Void return;

	/** Update connection event handlers **/
	@:hlNative('discord_rpc', 'update_handlers')
	public static function updateHandlers(handlers:DiscordEventHandlers):Void return;
}