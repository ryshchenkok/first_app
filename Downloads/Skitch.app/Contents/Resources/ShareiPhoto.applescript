try
	tell application id "com.apple.iphoto"
		import from "%@"
		activate
	end tell
on error error_message number error_number
	if the error_number is not -128 then
		beep
		display dialog error_message buttons {"Cancel"} default button 1
	end if
end try
