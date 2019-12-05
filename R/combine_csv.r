library(dplyr)
options(warn=2)


board = function(df){
  clnnm= colnames(df)
  if("River" %in% clnnm){
    return(paste(df$Flop, df$Turn, df$River))
  }
  
  if("Turn" %in% clnnm){
    
    return(paste(df$Flop, df$Turn))
    
  }
  
  return (df$Flop)
  
  
}

getSimple = function(df){
  
  return(ifelse(grepl("*C-FD*|\\bGS|\\bOE", df$Cat), "Good Draw", 
                ifelse(grepl("*PPu*",df$Cat), "PP",
                       ifelse(grepl("Overpair|Top-Pr", df$Cat), "Top Pair Plus", 
                              ifelse(grepl("*-Pr", df$Cat), "Pair",
                                     ifelse(grepl("^A-H$|^K-H$|^Q-H|*BFD*", df$Cat), "Weak Draw",
                                            ifelse(grepl("Air", df$Cat), "Air", 
                                                   ifelse(is.na(df$Cat), NA, "Two-Pair Plus"))))))))
  
}

getSimpleRiver = function(df){
  
  return(ifelse(grepl("\\b4Flush|\\b5Flush", df$Cat), "4C+Flush", 
                ifelse(grepl("Overpair|Top-Pr", df$Cat), "Top Pair Plus", 
                       ifelse(grepl("PPuTP|Second-Pr", df$Cat), "Second Pair Plus", 
                              ifelse(grepl("PPu2ndPr|Third-Pr", df$Cat), "Third Pair Plus", 
                                     ifelse(grepl("*-Pr", df$Cat), "Pair",
                                            ifelse(grepl("*PPu*",df$Cat), "PP",
                                                   ifelse(grepl("^A-H$", df$Cat), "A-H",
                                                          ifelse(grepl("^K-H$", df$Cat), "K-H",
                                                                 ifelse(grepl("^Q-H$", df$Cat), "Q-H",
                                                                        ifelse(grepl("Air", df$Cat), "Air", 
                                                                               ifelse(is.na(df$Cat), NA, "Two-Pair Plus"))))))))))))
  
}


read.cat = function(filename, hcfilename=NULL){
  if(!exists(hcfilename)){
    hcfilename = paste(gsub('.{4}$','',filename),"HandCat.csv",sep="")
    
 
   
    if(!file.exists(hcfilename)){
      
      if(.Platform$OS.type == "unix") {
        system(paste("HandClassifier", filename))
      } else {
        
      warning("No Classification File Found")
      
      
    }
    
    
  }
  
  }

  
  hnds = read.csv(filename, header=TRUE)
  hnds$Board=board(hnds)
  ctgrs= read.csv(hcfilename, header=TRUE)
  dh=inner_join(ctgrs,hnds, by=c("Board","Hand"))
  dh$Cat=ifelse(!grepl("NoDraw", dh$Draw) & grepl("-H$|Air", dh$Cat), as.character(dh$Draw), as.character(dh$Cat))
  dh$Cat = as.factor(dh$Cat)
  dh$FlushPossible = ifelse(str_count(dh$Board,"s") >= 3, TRUE, FALSE)

  dh$Simple = getSimple(dh)
  dh$Simple = factor(dh$Simple, levels = SIMPLE)
  
  dh$SR = getSimpleRiver(dh)
  
  dh$SR = ordered(dh$SR, levels=c("Two-Pair Plus", "Top Pair Plus", "Second Pair Plus", "Third Pair Plus","Pair", "PP", "A-H", "K-H", "Q-H", "Air", "4C+Flush"))
  
  
  return(dh)
  
  
  
}


