# My rules for having both qwerty and steno enabled at the same time
1. Steno layer is enabled by default
2. Whenever a key is typed after a pause (probably at least 0.6s)
    - if first key typed is a single, sharp key press
      - treat it as a qwerty key
      - and disable steno layer while any subsequent keys are pressed
3. Steno layer becomes enabled again after the next pause (probably of at least 0.6s)

# Consequences of above rules
- Normal typing of qwerty seems to "just work"
  - The only small exception
    - You just need to make sure that > your first keypresses after any pauses are sharp and distinct
      - after that, you can slur your presses and releases
- Normal typing of steno seems to "just work"
  - The only small exception
    - You just need to make sure that > if you want to type single-key steno strokes after any pauses, you hold them down for at least a tiny amount of time
      - to distinguish it from > a qwerty key
      - but, they can still be a relatively quick strokes - just not overly sharp ones
- alternating between qwerty and steno strokes works mostly seamlessly
  - You just have to pause a slight amount when going from one to the other 
- Weirdness of qwerty letters appearing only upon key release is mostly mitigated
  - only single keys typed after a pause will have that happen
    - all subsequent keys will appear as keys are pressed
- Weirdness of letters having to be deleted will be avoided
  - since we're defaulting to steno rather than qwerty
- Normal key repeat for qwerty keys mostly works
  - You just have to do a sharp press and then hold the key down
