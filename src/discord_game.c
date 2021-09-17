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
			strcpy(code, "DiscordResult_Ok");
			break;
		case DiscordResult_ServiceUnavailable:
			strcpy(code, "DiscordResult_ServiceUnavailable");
			break;
		case DiscordResult_InvalidVersion:
			strcpy(code, "DiscordResult_InvalidVersion");
			break;
		case DiscordResult_LockFailed:
			strcpy(code, "DiscordResult_LockFailed");
			break;
		case DiscordResult_InternalError:
			strcpy(code, "DiscordResult_InternalError");
			break;
		case DiscordResult_InvalidPayload:
			strcpy(code, "DiscordResult_InvalidPayload");
			break;
		case DiscordResult_InvalidCommand:
			strcpy(code, "DiscordResult_InvalidCommand");
			break;
		case DiscordResult_InvalidPermissions:
			strcpy(code, "DiscordResult_InvalidPermissions");
			break;
		case DiscordResult_NotFetched:
			strcpy(code, "DiscordResult_NotFetched");
			break;
		case DiscordResult_NotFound:
			strcpy(code, "DiscordResult_NotFound");
			break;
		case DiscordResult_Conflict:
			strcpy(code, "DiscordResult_Conflict");
			break;
		case DiscordResult_InvalidSecret:
			strcpy(code, "DiscordResult_InvalidSecret");
			break;
		case DiscordResult_InvalidJoinSecret:
			strcpy(code, "DiscordResult_InvalidJoinSecret");
			break;
		case DiscordResult_NoEligibleActivity:
			strcpy(code, "DiscordResult_NoEligibleActivity");
			break;
		case DiscordResult_InvalidInvite:
			strcpy(code, "DiscordResult_InvalidInvite");
			break;
		case DiscordResult_NotAuthenticated:
			strcpy(code, "DiscordResult_NotAuthenticated");
			break;
		case DiscordResult_InvalidAccessToken:
			strcpy(code, "DiscordResult_InvalidAccessToken");
			break;
		case DiscordResult_ApplicationMismatch:
			strcpy(code, "DiscordResult_ApplicationMismatch");
			break;
		case DiscordResult_InvalidDataUrl:
			strcpy(code, "DiscordResult_InvalidDataUrl");
			break;
		case DiscordResult_InvalidBase64:
			strcpy(code, "DiscordResult_InvalidBase64");
			break;
		case DiscordResult_NotFiltered:
			strcpy(code, "DiscordResult_NotFiltered");
			break;
		case DiscordResult_LobbyFull:
			strcpy(code, "DiscordResult_LobbyFull");
			break;
		case DiscordResult_InvalidLobbySecret:
			strcpy(code, "DiscordResult_InvalidLobbySecret");
			break;
		case DiscordResult_InvalidFilename:
			strcpy(code, "DiscordResult_InvalidFilename");
			break;
		case DiscordResult_InvalidFileSize:
			strcpy(code, "DiscordResult_InvalidFileSize");
			break;
		case DiscordResult_InvalidEntitlement:
			strcpy(code, "DiscordResult_InvalidEntitlement");
			break;
		case DiscordResult_NotInstalled:
			strcpy(code, "DiscordResult_NotInstalled");
			break;
		case DiscordResult_NotRunning:
			strcpy(code, "DiscordResult_NotRunning");
			break;
		case DiscordResult_InsufficientBuffer:
			strcpy(code, "DiscordResult_InsufficientBuffer");
			break;
		case DiscordResult_PurchaseCanceled:
			strcpy(code, "DiscordResult_PurchaseCanceled");
			break;
		case DiscordResult_InvalidGuild:
			strcpy(code, "DiscordResult_InvalidGuild");
			break;
		case DiscordResult_InvalidEvent:
			strcpy(code, "DiscordResult_InvalidEvent");
			break;
		case DiscordResult_InvalidChannel:
			strcpy(code, "DiscordResult_InvalidChannel");
			break;
		case DiscordResult_InvalidOrigin:
			strcpy(code, "DiscordResult_InvalidOrigin");
			break;
		case DiscordResult_RateLimited:
			strcpy(code, "DiscordResult_RateLimited");
			break;
		case DiscordResult_OAuth2Error:
			strcpy(code, "DiscordResult_OAuth2Error");
			break;
		case DiscordResult_SelectChannelTimeout:
			strcpy(code, "DiscordResult_SelectChannelTimeout");
			break;
		case DiscordResult_GetGuildTimeout:
			strcpy(code, "DiscordResult_GetGuildTimeout");
			break;
		case DiscordResult_SelectVoiceForceRequired:
			strcpy(code, "DiscordResult_SelectVoiceForceRequired");
			break;
		case DiscordResult_CaptureShortcutAlreadyListening:
			strcpy(code, "DiscordResult_CaptureShortcutAlreadyListening");
			break;
		case DiscordResult_UnauthorizedForAchievement:
			strcpy(code, "DiscordResult_UnauthorizedForAchievement");
			break;
		case DiscordResult_InvalidGiftCode:
			strcpy(code, "DiscordResult_InvalidGiftCode");
			break;
		case DiscordResult_PurchaseError:
			strcpy(code, "DiscordResult_PurchaseError");
			break;
		case DiscordResult_TransactionAborted:
			strcpy(code, "DiscordResult_TransactionAborted");
			break;
		default: 
			strcpy(code, "default");
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
