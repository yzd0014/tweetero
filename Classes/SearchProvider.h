//
//  SearchProvider.h
//  Tweetero
//
//  Created by Sergey Shkrabak on 10/16/09.
//  Copyright 2009 Codeminders. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MGTwitterEngineDelegate.h"

@class MGTwitterEngine;

typedef enum {
    SPInvalidValue = -1,
    SPUpdateState,
    SPSavedSearch,
    SPSearchData
} SPNotificationValue;

@interface SearchProvider : NSObject <MGTwitterEngineDelegate>
{
    NSMutableDictionary     *_queries;
    NSMutableDictionary     *_twitterConnection;
    MGTwitterEngine         *_twitter;
    id                       _delegate;
}

@property (nonatomic, readonly) MGTwitterEngine *twitter;
@property (nonatomic, retain) id delegate;

// Allocate and return SearchProvider object. Object is autoreleased.
+ (SearchProvider *)providerWithDelegate:(id)delegate;

- (id)initWithDelegate:(id)delegate;

// Update object
- (void)update;

// Return YES if query string present in dictionary
- (BOOL)hasQuery:(NSString *)query;

// Return YES if query with query id present in dictionary
- (BOOL)hasQueryById:(int)queryId;

// Save query string in tweeter
- (void)saveQuery:(NSString *)query forId:(int)queryId;

// Remove saved search query
- (void)removeQuery:(NSString *)query;

// Remove saved search query with query id
- (void)removeQueryById:(int)queryId;

// Return query string by id
- (NSString *)queryById:(int)queryId;

// Return id for query string
- (int)queryId:(NSString *)query;

// Return queries array
- (NSArray *)allQueries;

@end

@interface SearchProvider(SearchMethods)

// Search query in twitter
- (void)search:(NSString *)query;

// Search query in twitter with page and count data
- (void)search:(NSString *)query fromPage:(int)page count:(int)count;

// Search query in twitter with query id
- (void)searchForQueryId:(int)queryId;

// Search query in twitter with query id
- (void)searchForQueryId:(int)queryId fromPage:(int)page count:(int)count;

// Request twitter saved search
- (void)savedSearch;

@end

// SearchProvider Delegate
@protocol SearchProviderDelegate
@optional
- (void)searchDidEnd:(NSArray *)recievedData forQuery:(NSString *)query;
- (void)searchDidEndWithError:(NSString *)query;
- (void)searchSavedSearchReceived:(NSArray *)savedSearch;
- (void)searchProviderDidUpdated;
@end