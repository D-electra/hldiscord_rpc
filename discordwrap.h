#pragma once

#define HL_NAME(n) discord_rpc_##n
#include "hl.h"

#include "discord_rpc.h"

typedef struct {
	hl_type* t;
	vbyte* state;
	vbyte* details;
	int64_t startTimestamp;
	int64_t endTimestamp;
	vbyte* largeImageKey;
	vbyte* largeImageText;
	vbyte* smallImageKey;
	vbyte* smallImageText;
	vbyte* partyId;
	int partySize;
	int partyMax;
	vbyte* matchSecret;
	vbyte* joinSecret;
	vbyte* spectateSecret;
	int8_t instance;
} vpresence;

typedef struct {
	hl_type* t;
	vclosure* ready;
	vclosure* disconnected;
	vclosure* errored;
	vclosure* joinGame;
	vclosure* spectateGame;
	vclosure* joinRequest;
} vhandlers;

bool initialized = false;

vhandlers* current_handlers = nullptr;
DiscordEventHandlers* set_handlers(vhandlers* handlers) {
	if (current_handlers != nullptr) {
		hl_remove_root(current_handlers->ready);
		hl_remove_root(current_handlers->disconnected);
		hl_remove_root(current_handlers->errored);
		hl_remove_root(current_handlers->joinGame);
		hl_remove_root(current_handlers->spectateGame);
		hl_remove_root(current_handlers->joinRequest);
	}
	current_handlers = handlers;
	hl_add_root(current_handlers->ready);
	hl_add_root(current_handlers->disconnected);
	hl_add_root(current_handlers->errored);
	hl_add_root(current_handlers->joinGame);
	hl_add_root(current_handlers->spectateGame);
	hl_add_root(current_handlers->joinRequest);

	DiscordEventHandlers out;
	memset(&out, 0, sizeof(out));

	out.ready = [](const DiscordUser* request) {
		initialized = true;
		printf("Discord-RPC Initialized\n");

		vdynamic args[4];
		vdynamic* vargs[4] = { &args[0], &args[1], &args[2], &args[3] };
		args[0].t = &hlt_bytes;
		args[0].v.bytes = (vbyte*)request->userId;
		args[1].t = &hlt_bytes;
		args[1].v.bytes = (vbyte*)request->username;
		args[2].t = &hlt_bytes;
		args[2].v.bytes = (vbyte*)request->discriminator;
		args[3].t = &hlt_bytes;
		args[3].v.bytes = (vbyte*)request->avatar;
		hl_dyn_call(current_handlers->ready, vargs, 4);
	};
	out.disconnected = [](int errorCode, const char* message) {
		vdynamic args[2];
		vdynamic* vargs[2] = { &args[0], &args[1] };
		args[0].t = &hlt_i32;
		args[0].v.i = errorCode;
		args[1].t = &hlt_bytes;
		args[1].v.bytes = (vbyte*)message;
		hl_dyn_call(current_handlers->disconnected, vargs, 2);
	};
	out.errored = [](int errorCode, const char* message) {
		vdynamic args[2];
		vdynamic* vargs[2] = { &args[0], &args[1] };
		args[0].t = &hlt_i32;
		args[0].v.i = errorCode;
		args[1].t = &hlt_bytes;
		args[1].v.bytes = (vbyte*)message;
		hl_dyn_call(current_handlers->errored, vargs, 2);
	};
	out.joinGame = [](const char* joinSecret) {
		vdynamic args[1];
		vdynamic* vargs[1] = { &args[0] };
		args[0].t = &hlt_bytes;
		args[0].v.bytes = (vbyte*)joinSecret;
		hl_dyn_call(current_handlers->joinGame, vargs, 1);
	};
	out.spectateGame = [](const char* spectateSecret) {
		vdynamic args[1];
		vdynamic* vargs[1] = { &args[0] };
		args[0].t = &hlt_bytes;
		args[0].v.bytes = (vbyte*)spectateSecret;
		hl_dyn_call(current_handlers->spectateGame, vargs, 1);
	};
	out.joinRequest = [](const DiscordUser* request) {
		vdynamic args[4];
		vdynamic* vargs[4] = { &args[0], &args[1], &args[2], &args[3] };
		args[0].t = &hlt_bytes;
		args[0].v.bytes = (vbyte*)request->userId;
		args[1].t = &hlt_bytes;
		args[1].v.bytes = (vbyte*)request->username;
		args[2].t = &hlt_bytes;
		args[2].v.bytes = (vbyte*)request->discriminator;
		args[3].t = &hlt_bytes;
		args[3].v.bytes = (vbyte*)request->avatar;
		hl_dyn_call(current_handlers->joinRequest, vargs, 4);
	};

	/*DiscordUser user{};
	user.userId = "123";
	user.username = "TEST BUDDY";
	user.discriminator = "bud.dy";
	user.avatar = "icon";
	out.ready(&user);*/

	return &out;
}

DiscordRichPresence* wrap_presence(vpresence* presence) {
	vpresence in = *presence;
	DiscordRichPresence out;
	memset(&out, 0, sizeof(out));

	out.state = (const char*)in.state;
	out.details = (const char*)in.details;
	out.startTimestamp = in.startTimestamp;
	out.endTimestamp = in.endTimestamp;
	out.largeImageKey = (const char*)in.largeImageKey;
	out.largeImageText = (const char*)in.largeImageText;
	out.smallImageKey = (const char*)in.smallImageKey;
	out.smallImageText = (const char*)in.smallImageText;
	out.partyId = (const char*)in.partyId;
	out.partySize = in.partySize;
	out.partyMax = in.partyMax;
	out.matchSecret = (const char*)in.matchSecret;
	out.joinSecret = (const char*)in.joinSecret;
	out.spectateSecret = (const char*)in.spectateSecret;
	out.instance = in.instance;

	return &out;
}

HL_PRIM void HL_NAME(initialize)(vbyte* applicationId, vhandlers* handlers, int autoRegister, vbyte* optionalSteamId) {
	DiscordEventHandlers* _handlers = set_handlers(handlers);
	Discord_Initialize((const char*)applicationId, _handlers, autoRegister, (const char*)optionalSteamId);
}

HL_PRIM void HL_NAME(shutdown)() {
	initialized = false;
	Discord_Shutdown();
}

HL_PRIM void HL_NAME(run_callbacks)() {
	if (initialized) Discord_RunCallbacks();
}

HL_PRIM void HL_NAME(update_presence)(vpresence* presence) {
	Discord_UpdatePresence(wrap_presence(presence));
}

HL_PRIM void HL_NAME(clear_presence)() {
	Discord_ClearPresence();
}

HL_PRIM void HL_NAME(respond)(vbyte* userid, int reply) {
	Discord_Respond((const char*)userid, reply);
}

HL_PRIM void HL_NAME(update_handlers)(vhandlers* handlers) {
	DiscordEventHandlers* _handlers = set_handlers(handlers);
	Discord_UpdateHandlers(_handlers);
}