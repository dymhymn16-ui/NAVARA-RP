// Variable declarations
new TOTALBOARDS;

// Enum for the board structure: Name and Count
enum enumboard {
    lName[32],      // Store name of player/team
    lCount          // Store count for the respective category
};

// Leaderboard array, 10 entries, 4 categories, each with enumboard structure
new LeaderBoard[10][4][enumboard];

// 3D text labels for leaderboards
new Text3D:LeaderBoard3DText[4];

// Forward declarations
forward LeaderBoards();
public LeaderBoards()
{
    // Temporary variables for cache data
    new r, f;
    cache_get_data(r, f);   // Get leaderboard data from the database

    if(!r) return 1;  // If no data is available, return

    // Loop through and load the leaderboard data
    for(new i = 0; i < r; i++)
    {
        // Populate data for the four categories of leaderboard
        cache_get_field_content(i, "CaptureSeasonName", LeaderBoard[i][0][lName], sql_connection, 32);
        LeaderBoard[i][0][lCount] = cache_get_field_content_int(i, "CaptureSeasonCount", sql_connection);
        
        cache_get_field_content(i, "KillerSeasonName", LeaderBoard[i][1][lName], sql_connection, 32);
        LeaderBoard[i][1][lCount] = cache_get_field_content_int(i, "KillerSeasonCount", sql_connection);
        
        cache_get_field_content(i, "CaptureName", LeaderBoard[i][2][lName], sql_connection, 32);
        LeaderBoard[i][2][lCount] = cache_get_field_content_int(i, "CaptureCount", sql_connection);
        
        cache_get_field_content(i, "KillerName", LeaderBoard[i][3][lName], sql_connection, 32);
        LeaderBoard[i][3][lCount] = cache_get_field_content_int(i, "KillerCount", sql_connection);
        
        TOTALBOARDS++;  // Increment total boards counter
    }

    // Log the number of loaded leaderboards
    printf("[SERVER] %d leaderboards loaded.", TOTALBOARDS);

    // Create dynamic 3D text labels for leaderboards
    LeaderBoard3DText[3] = CreateDynamic3DTextLabel("Loading...", 0xFF7DF23E, 1799.114014, -1882.788208, 16.568600, 20.000000, 65535, 65535, 1);
    LeaderBoard3DText[2] = CreateDynamic3DTextLabel("Loading...", 0xFF7DF23E, 1796.114014, -1882.788208, 16.568600, 20.000000, 65535, 65535, 1);
    LeaderBoard3DText[1] = CreateDynamic3DTextLabel("Loading...", 0xFF7DF23E, 1793.114014, -1882.788208, 16.568600, 20.000000, 65535, 65535, 1);
    LeaderBoard3DText[0] = CreateDynamic3DTextLabel("Loading...", 0xFF7DF23E, 1790.114014, -1882.788208, 16.568600, 20.000000, 65535, 65535, 1);

    // Update the leaderboard display
    UpdateLeaderboards();
    
    return 1;
}

// Function to update leaderboard scores
stock UpdateScores(l_id, count, nsame[])
{
    // Check if the score already exists for the player/team
    new existt = CheckExistScore(l_id, nsame);
    if(existt) {
        existt--;  // Decrement to match array index
        for(new i; i < 10; i++)
        {
            if(existt == i)  // Found the score entry
            {
                // Create a temporary board to store previous data
                new tempBoard[10][4][enumboard];
                for(new ix = i; ix < 10; ix++)
                {
                    format(tempBoard[ix][l_id][lName], 32, "%s", LeaderBoard[ix][l_id][lName]);
                    tempBoard[ix][l_id][lCount] = LeaderBoard[ix][l_id][lCount];
                }

                // Shift leaderboard entries
                for(new ix = i; ix < 10; ix++)
                {
                    if(ix == 9)
                    {
                        LeaderBoard[ix][l_id][lName] = EOS;
                        LeaderBoard[ix][l_id][lCount] = 0;
                    }
                    else
                    {
                        format(LeaderBoard[ix][l_id][lName], 32, "%s", tempBoard[ix + 1][l_id][lName]);
                        LeaderBoard[ix][l_id][lCount] = tempBoard[ix + 1][l_id][lCount];
                    }
                }
                break;
            }
        }
    }

    // Check if the new score is higher than any existing scores
    for(new i; i < 10; i++)
    {
        if(count > LeaderBoard[i][l_id][lCount])  // New score is greater than the current
        {
            // Create a temporary board to store the data
            new tempBoard[10][4][enumboard];
            for(new ix = i; ix < 10; ix++)
            {
                format(tempBoard[ix][l_id][lName], 32, "%s", LeaderBoard[ix][l_id][lName]);
                tempBoard[ix][l_id][lCount] = LeaderBoard[ix][l_id][lCount];
            }

            // Shift leaderboard entries to make space for the new score
            for(new ix = i; ix < 10; ix++)
            {
                if(ix - 1 > 0 && i != ix) if(strcmp(LeaderBoard[ix][l_id][lName], LeaderBoard[ix - 1][l_id][lName], true) == 0) {
                    continue;
                }
                format(LeaderBoard[ix + 1][l_id][lName], 32, "%s", tempBoard[ix][l_id][lName]);
                LeaderBoard[ix + 1][l_id][lCount] = tempBoard[ix][l_id][lCount];
            }

            // Insert the new score into the leaderboard
            format(LeaderBoard[i][l_id][lName], 32, "%s", nsame);
            LeaderBoard[i][l_id][lCount] = count;

            // Update and save the leaderboards
            UpdateLeaderboards();
            SaveLeaderBoards();
            break;
        }
    }
}

// Function to check if the score already exists
stock CheckExistScore(l_id, nsame[])
{
    for(new i; i < 10; i++)
    {
        if(strcmp(nsame, LeaderBoard[i][l_id][lName], true) == 0 && strlen(LeaderBoard[i][l_id][lName])) {
            return i + 1;  // Score exists, return index
        }
    }
    return 0;  // No score found
}

// Function to save leaderboard data to the database
stock SaveLeaderBoards()
{
    new sql_string[256];
    for(new i; i < 10; i++)
    {
        // Update each leaderboard entry in the database
        mysql_format(sql_connection, sql_string, sizeof(sql_string), "UPDATE `leaderboards` SET `CaptureSeasonName` = '%s', `CaptureSeasonCount` = '%d' WHERE `id` = '%i'", LeaderBoard[i][0][lName], LeaderBoard[i][0][lCount], i + 1);
        mysql_tquery(sql_connection, sql_string);

        mysql_format(sql_connection, sql_string, sizeof(sql_string), "UPDATE `leaderboards` SET `KillerSeasonName` = '%s', `KillerSeasonCount` = '%d' WHERE `id` = '%i'", LeaderBoard[i][1][lName], LeaderBoard[i][1][lCount], i + 1);
        mysql_tquery(sql_connection, sql_string);

        mysql_format(sql_connection, sql_string, sizeof(sql_string), "UPDATE `leaderboards` SET `CaptureName` = '%s', `CaptureCount` = '%d' WHERE `id` = '%i'", LeaderBoard[i][2][lName], LeaderBoard[i][2][lCount], i + 1);
        mysql_tquery(sql_connection, sql_string);

        mysql_format(sql_connection, sql_string, sizeof(sql_string), "UPDATE `leaderboards` SET `KillerName` = '%s', `KillerCount` = '%d' WHERE `id` = '%i'", LeaderBoard[i][3][lName], LeaderBoard[i][3][lCount], i + 1);
        mysql_tquery(sql_connection, sql_string);
    }
}

// Function to update the leaderboard display
stock UpdateLeaderboards()
{
    new boardstring[] = EOS,
        orderstring[] = EOS;

    // Format leaderboard for the top "Capture" leaderboard
    for(new i; i < 5; i++)
    {
        if(LeaderBoard[i][0][lCount] == 0) continue;
        format(orderstring, sizeof(orderstring), "%s{FF0000}%d. {FFFF00}%s : {FFFFFF}%d\n", orderstring, i + 1, LeaderBoard[i][0][lName], LeaderBoard[i][0][lCount]);
    }

    format(boardstring, sizeof(boardstring), ""c_server"Top Gang Captures Sesson Leaderboard\n\
    {FFD700}____________________\n\n\
    %s\
    {FFD700}____________________\n", orderstring);

    UpdateDynamic3DTextLabelText(LeaderBoard3DText[3], -1, boardstring);

    // Format leaderboard for the top "Killer" leaderboard
    orderstring[0] = EOS;
    for(new i; i < 10; i++)
    {
        if(LeaderBoard[i][1][lCount] == 0) continue;
        format(orderstring, sizeof(orderstring), "%s{FF0000}%d. {FFFF00}%s : {FFFFFF}%d\n", orderstring, i + 1, LeaderBoard[i][1][lName], LeaderBoard[i][1][lCount]);
    }

    format(boardstring, sizeof(boardstring), ""c_server"Top Gang Sesson Killers Leaderboard\n\
    {FFD700}____________________\n\n\
    %s\
    {FFD700}____________________\n", orderstring);

    UpdateDynamic3DTextLabelText(LeaderBoard3DText[2], -1, boardstring);
}

cmd:resetseason(playerid)
{
	if(check_admin_rank(playerid , 6)) return 1;
	
    mysql_query(sql_connection,"UPDATE `users` SET `seasoncaptures` = '0', `seasonkills` = '0'");
	mysql_query(sql_connection,"UPDATE `leaderboards` SET `CaptureSeasonCount` = '0',  `CaptureSeasonName` = '', `KillerSeasonCount` = '0',  `KillerSeasonName` = ''");
	
    for(new i; i < 10; i++)
	{
		LeaderBoard[i][0][lName] = EOS;
		LeaderBoard[i][1][lName] = EOS;
		LeaderBoard[i][0][lCount] = 0;
		LeaderBoard[i][1][lCount] = 0;
	}

	UpdateLeaderboards();

	return SendAccess(playerid, "Season ba movafaghiat reset shod.");
}