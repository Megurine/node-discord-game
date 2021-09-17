#include "discord_game.h"

static void Destroy(napi_env env, void* data, void* hint) {
  if (!data) {
    return;
  }

  AddonState* state = (AddonState*)data;
  Application *app = &state->app;

  if (state->initialized && app->core) {
    app->core->destroy(app->core);
  }

  free(state);
}

//Char to int64
int64_t S64(const char *s) {
  int64_t i;
  char c ;
  int scanned = sscanf(s, "%" SCNd64 "%c", &i, &c);
  if (scanned == 1) return i;
  if (scanned > 1) {
    // TBD about extra data found
    return i;
    }
  // TBD failed to scan;  
  return 0;  
}

char* DiscordResultToChar(enum EDiscordResult e)
{
	static char code[128] = "Before switch";
	switch(e){
		case DiscordResult_Ok:
			char newcode[128] = "DiscordResult_Ok";
			strcpy(code, newcode);
			break;
		case DiscordResult_ServiceUnavailable:
			char newcode1[128] = "DiscordResult_ServiceUnavailable";
			strcpy(code, newcode1);
			break;
		case DiscordResult_InvalidVersion:
			char newcode2[128] = "DiscordResult_InvalidVersion";
			strcpy(code, newcode2);
			break;
		case DiscordResult_LockFailed:
			char newcode3[128] = "DiscordResult_LockFailed";
			strcpy(code, newcode3);
			break;
		case DiscordResult_InternalError:
			char newcode4[128] = "DiscordResult_InternalError";
			strcpy(code, newcode4);
			break;
		case DiscordResult_InvalidPayload:
			char newcode5[128] = "DiscordResult_InvalidPayload";
			strcpy(code, newcode5);
			break;
		case DiscordResult_InvalidCommand:
			char newcode6[128] = "DiscordResult_InvalidCommand";
			strcpy(code, newcode6);
			break;
		case DiscordResult_InvalidPermissions:
			char newcode7[128] = "DiscordResult_InvalidPermissions";
			strcpy(code, newcode7);
			break;
		case DiscordResult_NotFetched:
			char newcode8[128] = "DiscordResult_NotFetched";
			strcpy(code, newcode8);
			break;
		case DiscordResult_NotFound:
			char newcode9[128] = "DiscordResult_NotFound";
			strcpy(code, newcode9);
			break;
		case DiscordResult_Conflict:
			char newcode10[128] = "DiscordResult_Conflict";
			strcpy(code, newcode10);
			break;
		case DiscordResult_InvalidSecret:
			char newcode11[128] = "DiscordResult_InvalidSecret";
			strcpy(code, newcode11);
			break;
		case DiscordResult_InvalidJoinSecret:
			char newcode12[128] = "DiscordResult_InvalidJoinSecret";
			strcpy(code, newcode12);
			break;
		case DiscordResult_NoEligibleActivity:
			char newcode13[128] = "DiscordResult_NoEligibleActivity";
			strcpy(code, newcode13);
			break;
		case DiscordResult_InvalidInvite:
			char newcode14[128] = "DiscordResult_InvalidInvite";
			strcpy(code, newcode14);
			break;
		case DiscordResult_NotAuthenticated:
			char newcode15[128] = "DiscordResult_NotAuthenticated";
			strcpy(code, newcode15);
			break;
		case DiscordResult_InvalidAccessToken:
			char newcode16[128] = "DiscordResult_InvalidAccessToken";
			strcpy(code, newcode16);
			break;
		case DiscordResult_ApplicationMismatch:
			char newcode17[128] = "DiscordResult_ApplicationMismatch";
			strcpy(code, newcode17);
			break;
		case DiscordResult_InvalidDataUrl:
			char newcode18[128] = "DiscordResult_InvalidDataUrl";
			strcpy(code, newcode18);
			break;
		case DiscordResult_InvalidBase64:
			char newcode19[128] = "DiscordResult_InvalidBase64";
			strcpy(code, newcode19);
			break;
		case DiscordResult_NotFiltered:
			char newcode20[128] = "DiscordResult_NotFiltered";
			strcpy(code, newcode20);
			break;
		case DiscordResult_LobbyFull:
			char newcode21[128] = "DiscordResult_LobbyFull";
			strcpy(code, newcode21);
			break;
		case DiscordResult_InvalidLobbySecret:
			char newcode122[128] = "DiscordResult_InvalidLobbySecret";
			strcpy(code, newcode122);
			break;
		case DiscordResult_InvalidFilename:
			char newcode23[128] = "DiscordResult_InvalidFilename";
			strcpy(code, newcode23);
			break;
		case DiscordResult_InvalidFileSize:
			char newcode24[128] = "DiscordResult_InvalidFileSize";
			strcpy(code, newcode24);
			break;
		case DiscordResult_InvalidEntitlement:
			char newcode25[128] = "DiscordResult_InvalidEntitlement";
			strcpy(code, newcode25);
			break;
		case DiscordResult_NotInstalled:
			char newcode26[128] = "DiscordResult_NotInstalled";
			strcpy(code, newcode26);
			break;
		case DiscordResult_NotRunning:
			char newcode27[128] = "DiscordResult_NotRunning";
			strcpy(code, newcode27);
			break;
		case DiscordResult_InsufficientBuffer:
			char newcode28[128] = "DiscordResult_InsufficientBuffer";
			strcpy(code, newcode28);
			break;
		case DiscordResult_PurchaseCanceled:
			char newcode29[128] = "DiscordResult_PurchaseCanceled";
			strcpy(code, newcode29);
			break;
		case DiscordResult_InvalidGuild:
			char newcode30[128] = "DiscordResult_InvalidGuild";
			strcpy(code, newcode30);
			break;
		case DiscordResult_InvalidEvent:
			char newcode31[128] = "DiscordResult_InvalidEvent";
			strcpy(code, newcode31);
			break;
		case DiscordResult_InvalidChannel:
			char newcode32[128] = "DiscordResult_InvalidChannel";
			strcpy(code, newcode32);
			break;
		case DiscordResult_InvalidOrigin:
			char newcode33[128] = "DiscordResult_InvalidOrigin";
			strcpy(code, newcode33);
			break;
		case DiscordResult_RateLimited:
			char newcode34[128] = "DiscordResult_RateLimited";
			strcpy(code, newcode34);
			break;
		case DiscordResult_OAuth2Error:
			char newcode35[128] = "DiscordResult_OAuth2Error";
			strcpy(code, newcode35);
			break;
		case DiscordResult_SelectChannelTimeout:
			char newcode36[128] = "DiscordResult_SelectChannelTimeout";
			strcpy(code, newcode36);
			break;
		case DiscordResult_GetGuildTimeout:
			char newcode37[128] = "DiscordResult_GetGuildTimeout";
			strcpy(code, newcode37);
			break;
		case DiscordResult_SelectVoiceForceRequired:
			char newcode38[128] = "DiscordResult_SelectVoiceForceRequired";
			strcpy(code, newcode38);
			break;
		case DiscordResult_CaptureShortcutAlreadyListening:
			char newcode39[128] = "DiscordResult_CaptureShortcutAlreadyListening";
			strcpy(code, newcode39);
			break;
		case DiscordResult_UnauthorizedForAchievement:
			char newcode40[128] = "DiscordResult_UnauthorizedForAchievement";
			strcpy(code, newcode40);
			break;
		case DiscordResult_InvalidGiftCode:
			char newcode41[128] = "DiscordResult_InvalidGiftCode";
			strcpy(code, newcode41);
			break;
		case DiscordResult_PurchaseError:
			char newcode42[128] = "DiscordResult_PurchaseError";
			strcpy(code, newcode42);
			break;
		case DiscordResult_TransactionAborted:
			char newcode43[128] = "DiscordResult_TransactionAborted";
			strcpy(code, newcode43);
			break;
		default: 
			char newcoded[128] = "default";
			strcpy(code, newcoded);
	}
	
	return code;
}

napi_value RunCallback(napi_env env, napi_callback_info info) {
  void *data;
  AddonState *state;
  napi_value ret;

  NAPI_REQUIRE(napi_get_cb_info(env, info, 0, NULL, NULL, &data));
  state = data;

  if (!state->initialized) {
    NAPI_REQUIRE(napi_get_boolean(env, false, &ret));
    return ret;
  }

  enum EDiscordResult result;
  result = state->app.core->run_callbacks(state->app.core);

  
  char* code = DiscordResultToChar(result);
  if (result != DiscordResult_Ok) {
    NAPI_REQUIRE(napi_create_string_utf8(env, code, NAPI_AUTO_LENGTH, &ret));
    return ret;
  }

  NAPI_REQUIRE(napi_get_boolean(env, true, &ret));
  return ret;
}


napi_value Create(napi_env env, napi_callback_info info) {
  size_t argc = 2;
  napi_value argv[2];
  napi_value ret;
  void* data;
  AddonState *state;

  NAPI_REQUIRE(napi_get_cb_info(env, info, &argc, argv, NULL, &data));

  //char c;
  bool is_required;
  char raw_app_id[64];
  size_t buffer_size = 64;
  size_t copied;
  NAPI_REQUIRE(napi_get_value_string_utf8(env, argv[0], raw_app_id, buffer_size, &copied));
  NAPI_REQUIRE(napi_get_value_bool(env, argv[1], &is_required));
 
  int64_t app_id = S64(raw_app_id);

  state = data;
  memset(&state->app, 0, sizeof(state->app));
  memset(&state->users_events, 0, sizeof(state->users_events));
  memset(&state->activities_events, 0, sizeof(state->activities_events));
  memset(&state->relationships_events, 0, sizeof(state->relationships_events));


  //state->users_events.on_current_user_update = OnUserUpdated;

  Application *app = &state->app;


  struct DiscordCreateParams params;
  DiscordCreateParamsSetDefault(&params);
  params.client_id = (DiscordClientId)app_id;
  params.flags = is_required ? DiscordCreateFlags_Default : DiscordCreateFlags_NoRequireDiscord;
  params.event_data = state;
  params.activity_events = &state->activities_events;
  params.relationship_events = &state->relationships_events;
  params.user_events = &state->users_events;

  enum EDiscordResult result;
  result = DiscordCreate(DISCORD_VERSION, &params, &app->core);

  if (result != DiscordResult_Ok) {
    /*NAPI_REQUIRE(napi_get_boolean(env, false, &ret));
    return ret;*/
	char* code = DiscordResultToChar(result);
	NAPI_REQUIRE(napi_create_string_utf8(env, code, NAPI_AUTO_LENGTH, &ret));
	return ret;
  }

  app->users = app->core->get_user_manager(app->core);
  app->achievements = app->core->get_achievement_manager(app->core);
  app->activities = app->core->get_activity_manager(app->core);
  app->application = app->core->get_application_manager(app->core);
  app->lobbies = app->core->get_lobby_manager(app->core);
  app->relationships = app->core->get_relationship_manager(app->core);

  state->initialized = true;

  NAPI_REQUIRE(napi_get_boolean(env, true, &ret));
  return ret;
  /*char* code = DiscordResultToChar(result);
	NAPI_REQUIRE(napi_create_string_utf8(env, code, NAPI_AUTO_LENGTH, &ret));
	return ret;*/
}



napi_value GetUserId(napi_env env, napi_callback_info info) {
  void *data;
  AddonState *state;
  napi_value ret;

  NAPI_REQUIRE(napi_get_cb_info(env, info, 0, NULL, NULL, &data));
  state = data;
  
  if (!state->initialized) {
    NAPI_REQUIRE(napi_get_boolean(env, false, &ret));
    return ret;
  }

  
  struct DiscordUser current_user;
  memset(&current_user, 0, sizeof(current_user));

  enum EDiscordResult result;
  result = state->app.users->get_current_user(state->app.users, &current_user);

	
	//char* code = DiscordResultToChar(result);
	//NAPI_REQUIRE(napi_create_string_utf8(env, code, NAPI_AUTO_LENGTH, &ret));
	//return ret;
  
  if (result != DiscordResult_Ok) {
    NAPI_REQUIRE(napi_get_boolean(env, false, &ret));
    return ret;
  }

  napi_value userId;
  NAPI_REQUIRE(napi_create_bigint_int64(env, current_user.id, &userId));

  return userId;
}

napi_value GetUserIdName(napi_env env, napi_callback_info info) {
  void *data;
  AddonState *state;
  napi_value ret;

  NAPI_REQUIRE(napi_get_cb_info(env, info, 0, NULL, NULL, &data));
  state = data;
  
  if (!state->initialized) {
    NAPI_REQUIRE(napi_get_boolean(env, false, &ret));
    return ret;
  }
  
  struct DiscordUser current_user;
  memset(&current_user, 0, sizeof(current_user));

  enum EDiscordResult result;
  result = state->app.users->get_current_user(state->app.users, &current_user);
  
  if (result != DiscordResult_Ok) {
    NAPI_REQUIRE(napi_get_boolean(env, false, &ret));
    return ret;
  }

  napi_value username;
  NAPI_REQUIRE(napi_create_string_utf8(env, current_user.username, NAPI_AUTO_LENGTH, &username));

  return username;
}

napi_value Init(napi_env env, napi_value exports)
{
  // Setup Module State
  AddonState* state = malloc(sizeof(*state));
  state->initialized = false;
  napi_wrap(env, exports, state, Destroy, NULL, NULL);

  // Setup Objects
  napi_value version,
             application,
             activity;
  NAPI_REQUIRE(napi_create_uint32(env, DISCORD_VERSION, &version));
  application = Application_Init(env, state);
  activity = Activity_Init(env, state);

  napi_property_descriptor desc[] = {

    { "GetUserId", NULL, GetUserId, NULL, NULL, NULL, napi_default, state },
	{ "GetUserIdName", NULL, GetUserIdName, NULL, NULL, NULL, napi_default, state },
    { "version", NULL, NULL, NULL, NULL, version, napi_default, NULL },
    { "create", NULL, Create, NULL, NULL, NULL, napi_default, state },
    { "runCallback", NULL, RunCallback, NULL, NULL, NULL, napi_default, state },
    { "Application", NULL, NULL, NULL, NULL, application, napi_default, NULL },
    { "Activity", NULL, NULL, NULL, NULL, activity, napi_default, NULL }
  };

  NAPI_REQUIRE(napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
