#include <cstdint>

extern "C" {
	// Override the sanity check function
	// With -zmuldefs linker flag, this definition takes precedence over libnet80211.a
	// This allows deauth (0xC0), disassoc (0xA0), and auth frames to be transmitted
	int ieee80211_raw_frame_sanity_check(int32_t arg, int32_t arg2,
										 int32_t arg3) {
		// Always return 0 (success) - allow all frame types
		return 0;
	}
}
