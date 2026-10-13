# Later

## Song tool: "that one riff" -> a QMK jingle that actually sounds right

Tabs give pitches but not rhythm, and nobody here can listen to the output except Kohl. The speaker is
one voice, square waves, no dynamics, so a song is just (pitch, duration) pairs and correctness is a data
comparison. Plan, as a tools/ folder in this repo:

1. Reference -> notes: a MIDI file if one exists; otherwise a short clip of the recording through an
   audio-to-MIDI tool (Spotify basic-pitch, or librosa/aubio onset + pitch tracking), snapped to a
   sixteenth grid at the detected tempo.
2. Notes -> SONG(): handle the factor-of-four naming (W__NOTE is one beat, so a sixteenth is Q__NOTE at
   TEMPO_DEFAULT 120), rests between repeated pitches, transposing into the speaker's good range.
3. Simulate: render the note array to WAV with QMK's timing, compare to the reference note by note
   ("note 6 starts 60 ms late"), and render spectrograms of both as images for a visual check.
4. Hardware check: record the Moonlander's speaker with a mic, run the same analysis, to catch QMK's real
   timing (tempo, gaps between notes) that the simulation misses.

Commands: 'song.py midi-to-qmk', 'song.py render', 'song.py compare'.
First test: the full Megalovania intro, and whether the comparison agrees with Kohl's ear about the
one-bar riff in users/kohljary/user_song_list.h.

## Keymaps that don't build

keychron q8 (ansi_encoder, iso), q10, massdrop/alt (now keyboards/drop/alt). See README, Boards.
