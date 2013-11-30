#!/bin/bash

AlternativeArray=("Alternative/! Rapcore & Rap-Rock")

AudioBooksArray=("AudioBooks")

ClassicArray=(
"Classic/!1-Medieval (450-1430)"    "Classic/!2-Renaissance (1430-1600)"   "Classic/!3-Baroque (1650-1750)"
"Classic/!4-Classical (1765-1810)"  "Classic/!5-Romantic (1810-1910)"      "Classic/!6-20th century (1910-)"
"Classic/!Russian"
)

ElectronicArray=(
"Electronic/! MOD music from torrents.ru"    "Electronic/! Other"
"Electronic/!Beat, Breaks, Nu Breaks"        "Electronic/!Chillout"
"Electronic/!Dance"                          "Electronic/!Downtempo"
"Electronic/!Drum'n'Bass"                    "Electronic/!Electroclash"
"Electronic/!Happy Hardcore, Breakcore"      "Electronic/!House"
"Electronic/!IDM"                            "Electronic/!Lounge"
"Electronic/!Psy"                            "Electronic/!Techno"
"Electronic/!Tracker and 8 bit"              "Electronic/!Trance"
"Electronic/!Trip-Hop"                       "Electronic/!Various Artists"
)

FolkArray=(
"Folk/!African"                     "Folk/!American"                    "Folk/!Asian"
"Folk/!Celtic"                      "Folk/!Country"                     "Folk/!European"
"Folk/!Jewish"                      "Folk/-=World Compilations=-"       "Folk/-=Slavonic Compilations=-"
)

GrungeArray=(
"Grunge Indie/!Best New Music"                      "Grunge Indie/!Britpop"
"Grunge Indie/!Experimental & New Weird America"    "Grunge Indie/!Grunge"
"Grunge Indie/!Indie"                               "Grunge Indie/!Indie Electronic"
"Grunge Indie/!Indie Pop"                           "Grunge Indie/!Indie Rock"
"Grunge Indie/!lo-fi"                               "Grunge Indie/!Math Rock"
"Grunge Indie/!New Rave Disco-Punk"                 "Grunge Indie/!Noise-Rock"
"Grunge Indie/!Other"                               "Grunge Indie/!Post-Rock"
"Grunge Indie/!Russian Indie"                       "Grunge Indie/!Shoegaze"
"Grunge Indie/!Singer-Songwriter"                   "Grunge Indie/!temp"
"Grunge Indie/!Witch House"
)

MusicalsArray=("Musicals")

NewAgeArray=("New Age")

OtherArray=("Other")

PopArray=(
"Pop/!Chanson"                 "Pop/!Disco, Dance Pop"            "Pop/!East Asian Pop"
"Pop/!Latin Pop"               "Pop/!Middle Eastern Pop"          "Pop/!Pop Rock"
"Pop/!R'n'B, Soul Pop"         "Pop/!Synth Pop, New Wave"         "Pop/!Vocal, Easy Listening"
)

ReggaeArray=(
"Reggae Ska Dub/!Dancehall"                     "Reggae Ska Dub/!Dub"
"Reggae Ska Dub/!Dubstep"                       "Reggae Ska Dub/!Mento"
"Reggae Ska Dub/!Modern Reggae"                 "Reggae Ska Dub/!Reggaeton"
"Reggae Ska Dub/!Roots Reggae"                  "Reggae Ska Dub/!Ska"
"Reggae Ska Dub/=Dub Compilations="             "Reggae Ska Dub/=Reggae Compilations="
"Reggae Ska Dub/=Reggaeton Compilations="       "Reggae Ska Dub/=Ska Compilations="
"Reggae Ska Dub/_to delete"                     "Reggae Ska Dub/_unsorted"
)

RussianArray=(
"Russian/!Blues"               "Russian/!Electronic"           "Russian/!Folk"
"Russian/!Homemade"            "Russian/!Instrumental"         "Russian/!Jazz&Funk"
"Russian/!Other"               "Russian/!Reggae"               "Russian/!Various Попса"
"Russian/!Various Рок"         "Russian/!Various Эстрада"      "Russian/!Наше"
"Russian/!Попса"               "Russian/!Русский рок"          "Russian/!Эстрада"
)

SocialDancesArray=("Social Dances")

JazzArray=(
"Jazz/! 1 Dixieland,New Orleans,Swing"            "Jazz/! 2 Bop,Cool,Third Stream,Progressive"
"Jazz/! 3 Free,Avant-garde"                       "Jazz/! 4 Latin, World Fusion"
"Jazz/! 5 Fusion"                                 "Jazz/! 6 Funk, Soul"
"Jazz/! 7 Smooth,Acid,Electro"                    "Jazz/! 8 Vocal"
)
RockArray=("Rock")

RocknRollArray=(
"Rock-n-Roll/!Funk"                  "Rock-n-Roll/!Psychobilly"             "Rock-n-Roll/!R&B"
"Rock-n-Roll/!Rock-n-Roll"           "Rock-n-Roll/!Rockabilly"              "Rock-n-Roll/!Rockabilly Swing"
"Rock-n-Roll/!Surf")

SoundTracksArray=(
"Soundtracks/!Films")


#Soundtracks

#======================================================================================================
#======================================================================================================
#======================================================================================================


if [ -z "$1" ]
then
   echo "You forget to specify folder of natalie!"
   exit 1
fi

if [ "$1" = "Alternative" ]; then
   Array=("${AlternativeArray[@]}")
elif [ "$1" = "AudioBooks" ]; then
   Array=("${AudioBooksArray[@]}")
elif [ "$1" = "Classic" ]; then
   Array=("${ClassicArray[@]}")
elif [ "$1" = "Electronic" ]; then
   Array=("${ElectronicArray[@]}")
elif [ "$1" = "Folk" ]; then
   Array=("${FolkArray[@]}")
elif [ "$1" = "Grunge" ]; then
   Array=("${GrungeArray[@]}")
elif [ "$1" = "Musicals" ]; then
   Array=("${MusicalsArray[@]}")
elif [ "$1" = "NewAge" ]; then
   Array=("${NewAgeArray[@]}")
elif [ "$1" = "Other" ]; then
   Array=("${OtherArray[@]}")
elif [ "$1" = "Pop" ]; then
   Array=("${PopArray[@]}")
elif [ "$1" = "Reggae" ]; then
   Array=("${ReggaeArray[@]}")
elif [ "$1" = "Russian" ]; then
   Array=("${RussianArray[@]}")
elif [ "$1" = "SocialDances" ]; then
   Array=("${SocialDancesArray[@]}")
elif [ "$1" = "Jazz" ]; then
   Array=("${JazzArray[@]}")
elif [ "$1" = "Rock" ]; then
   Array=("${RockArray[@]}")
elif [ "$1" = "RocknRoll" ]; then
   Array=("${RocknRollArray[@]}")
elif [ "$1" = "SoundTracks" ]; then
   Array=("${SoundTracksArray[@]}")
else
   echo "There is no such folder on natalie!!!"
   exit 1
fi


#======================================================================================================


RAID_PATH=/mnt/media
NATALIE_PATH=/mnt/freedata/home/Void/samba/194.85.80.27/music

#--checksum - even if time of dst does not coincide with time of src it DOES NOT copy if files are equal
# without this iption if time of dst does not coincide with time of src rsync will perform transfer
RSYNC_OPTIONS="--times --recursive   --size-only       --verbose --human-readable --progress --itemize-changes --stats"

for ix in ${!Array[*]}
do
   echo; echo; echo; echo;
   echo "RSYNC ${NATALIE_PATH}/${Array[$ix]}/"  "${RAID_PATH}/natalie/${Array[$ix]}/"
   echo; 
   rsync ${RSYNC_OPTIONS} "${NATALIE_PATH}/${Array[$ix]}/"  "${RAID_PATH}/natalie/${Array[$ix]}/"
   echo "========================================================================================";
done
echo
