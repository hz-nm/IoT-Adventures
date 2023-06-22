/* <p>Creates a new item, or replaces an old item with a new item. If an item already exists in the specified 
table with the same primary key, the new item completely replaces the existing item. You can perform a conditional 
put (insert a new item if one with the specified primary key doesn't exist), or replace an existing item if it has 
certain attribute values. </p><p>In addition to putting an item, you can also return the item's attribute values in 
the same operation, using the <i>ReturnValues</i> parameter.</p><p>When you add an item, the primary key attribute(s) 
are the only required attributes. Attribute values cannot be null. String and binary type attributes must have lengths 
greater than zero. Set type attributes cannot be empty. Requests with empty values will be rejected 
with a <i>ValidationException</i>.</p><p>You can request that <i>PutItem</i> return either a copy of the old item (before the update) 
or a copy of the new item (after the update). For more information, 
see the <i>ReturnValues</i> description.</p><p>
For more information about using this API, see <a href="http://docs.aws.amazon.com/amazondynamodb/latest/developerguide/WorkingWithItems.html">Working with Items</a> in the Amazon DynamoDB Developer Guide.</p> */
    PutItemOutput putItem(PutItemInput putItemInput, ActionError& actionError, bool retry = true, int* httpStatusCode = NULL);