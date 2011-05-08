#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b

namespace SoyTracker
{
  enum Colors { CHANNEL_MARGIN_COLOR = 1, NOTE_COLOR, INSTRUMENT_COLOR, VOLUME_COLOR, EFFECT_NAME_COLOR, EFFECT_OPERAND_COLOR };
  enum InnerPosition { NOTE = 1, INSTRUMENT, VOLUME, EFFECT_NAME, EFFECT_OPERAND_HIGH, EFFECT_OPERAND_LOW };
}
