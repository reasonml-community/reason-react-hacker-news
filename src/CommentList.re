open Utils;

requireCSS("src/CommentList.css");

type action =
  | Toggle(option(string));

type state = {collapsed_comments: JSSet.set(int)};

let component = ReasonReact.reducerComponent("CommentList");
let make = (~story: HackerNews.story_with_comments, _children) => {
  let toggleComment = (collapsed, idMaybe: option(string)) =>
    switch idMaybe {
    | Some(idString) =>
      let id = int_of_string(idString);
      if (JSSet.has(collapsed, id)) {
        JSSet.remove(collapsed, id)
      } else {
        JSSet.add(collapsed, id)
      }
    | None => collapsed
    };

  /* let getCommentIdFromEvent = (event: ReactEventRe.Mouse.t) =>
    getAttribute(ReactDOMRe.domElementToObj(ReactEventRe.Mouse.currentTarget(event)), "name"); */

  /* let renderCommentText = (textMaybe: option(string)) =>
    switch textMaybe {
    | Some(text) => <div dangerouslySetInnerHTML=(dangerousHtml(text)) />
    | None => textEl("missing comment")
    }; */
/*
  let rec renderCommentKids = (self, comment: HackerNews.story_with_comments) =>
    renderCommentList(self, comment.comments)

  and  */
  let renderCommentList = (_self, _comments: array(HackerNews.story_with_comments)) =>
    <div />;

  {
    ...component,

    initialState: () => {
      collapsed_comments: JSSet.create([||]: array(int))
    },

    reducer: (action, state) =>
      switch action {
      | Toggle(commentId) =>
        ReasonReact.Update({
          collapsed_comments: toggleComment(state.collapsed_comments, commentId)
        })
      },

    render: (self) =>
      renderCommentList(self, story.comments)
  }
};
